#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct binary_tree {
  int item;
  struct binary_tree *left, *right;
} binary_tree;

binary_tree *create_empty_bt() {
return NULL;
}

binary_tree* create_binary_tree(int item, binary_tree *right, binary_tree *left) {
  binary_tree *raiz = (binary_tree *) malloc(sizeof(binary_tree));
  raiz->item = item;
  raiz->left = left;
  raiz->right = right;
return raiz;
}

int is_empty(binary_tree *bt) {
  if(bt == NULL)
    return 1;
return 0;
}

int count_nodes(binary_tree *raiz){
   if(raiz == NULL)
    return 0;
   else
    return 1 + count_nodes(raiz->left) + count_nodes(raiz->right);
}

int count_leafs(binary_tree *raiz){
   if(raiz == NULL)
        return 0;
   if(raiz->left == NULL && raiz->right == NULL)
        return 1;
return count_leafs(raiz->left) + count_leafs(raiz->right);
}

int verifica_maior_num(int a, int b){
  if(a > b)
    return a;
  else
    return b;
}

int altura(binary_tree *raiz) {
   if((raiz == NULL) || (raiz->left == NULL && raiz->right == NULL))
       return 0;
   else
       return 1 + verifica_maior_num(altura(raiz->left), altura(raiz->right));
}

binary_tree *verifica_maior_node(binary_tree *bt) {

  binary_tree *aux = bt;

  if(!is_empty(aux)) {
    while(!is_empty(aux->right)) {
      aux = aux->right;
    }
  }
return aux;
}

binary_tree *verifica_menor_node(binary_tree *bt) {
  binary_tree *aux = bt;

  if(!is_empty(aux)) {
    while(!is_empty(aux->left)) {
      aux = aux->left;
    }
  }
return aux;
}

int max_value(binary_tree *bt) {
  if (bt->right != NULL) 
    return max_value(bt->right);
  else 
    return bt->item;
}

int min_value(binary_tree *bt) {
  if (bt->left != NULL) 
    return min_value(bt->left);
  else 
    return bt->item;
}

binary_tree* insert(binary_tree *bt, int item) {
  if (bt == NULL)  {
    bt = create_binary_tree(item, NULL, NULL);
  }
  else if(bt->item > item) {
    bt->left = insert(bt->left, item);
    }
  else{
    bt->right = insert(bt->right, item);
    }
    
return bt;
}

binary_tree* search(binary_tree *bt, int item) {
  
  if ((bt == NULL) || (bt->item == item)) 
    return bt;

  else if (bt->item > item) 
    return search(bt->left, item);
  
  else 
    return search(bt->right, item);
}

int verifica_ordenada(binary_tree *bt) {
  int vetor_ordenacao[count_nodes(bt)], i=0;

  if(bt != NULL) {
    verifica_ordenada(bt->left);
    vetor_ordenacao[i] = bt->item;
    i++;

    verifica_ordenada(bt->right);
  }

  for(i=0; i <= (count_nodes(bt)); i++) {
    if(vetor_ordenacao[i] < vetor_ordenacao[i+1])
      continue;
    else
      return 1;
  }
return 0;
}

void print_in_order(binary_tree *bt) {
  if (bt != NULL) {
    print_in_order(bt->left);
    printf("%d ", bt->item);
    print_in_order(bt->right);
  }
}

void print_pre_order(binary_tree *bt) {
  if (!is_empty(bt)) {
    printf("%d ", bt->item);
    print_pre_order(bt->left);
    print_pre_order(bt->right);
  }
}

void print_post_order(binary_tree *bt) {
  if (!is_empty(bt)) {
    print_pre_order(bt->left);
    print_pre_order(bt->right);
    printf("%d ", bt->item);
  }
}

char* read_bracket_string() {
  char element,  *string = (char*)malloc(100 * sizeof(char));
  int open = 0, close = 0, i = 0;

  scanf("%c", &element);

  while(true) {
    
    if(element != ' ' && element != '\n') 
      string[i++] = element;
    
    if(element == '(') 
        open++;
    
    else if(element == ')') 
      close++;
        
    if(open == close) 
      break;
    
    scanf("%c", &element);
  }

  string[i] = '\0';

 // printf("%s", string);

return string;
}

binary_tree* construct_btree(char *string, int *i) {

  char str_num[5];
  int num, j = 0;

  binary_tree *bt = create_empty_bt();

  if(string[(*i)++] == '(') {
    if(string[*i] == ')') {
      (*i)++;
      return NULL;
    }

    while(string[*i] != '(') 
      str_num[j++] = string[(*i)++];
          
    str_num[j] = '\0';
    num = atoi(str_num);

    bt = create_binary_tree(num, NULL, NULL);
    bt->left = construct_btree(string, i);
    bt->right = construct_btree(string, i);
  }

  (*i)++;

return bt;
}

void generate_parenthesis_btree(binary_tree *bt) {
    printf("(");
    if(!is_empty(bt)) {
        printf("%d", bt->item);
        generate_parenthesis_btree(bt->left);
        generate_parenthesis_btree(bt->right);
    }
    printf(")");
}

int depth(binary_tree *bt, int item) {
  
  if ((bt == NULL) || (bt->item == item)) 
    return 0;

  else if (bt->item > item) 
    return 1 + depth(bt->left, item);
  
  else 
    return 1 + depth(bt->right, item);
}

int is_bst_aux(binary_tree *bt, int min, int max) {  

  if (bt==NULL)  
     return 1; 
        
  if (bt->item < min || bt->item > max)  
     return 0;  

  return 
    is_bst_aux(bt->left, min, bt->item-1) &&  
    is_bst_aux(bt->right, bt->item+1, max); 
}

int is_BST(binary_tree *bt)  {  
  return(is_bst_aux(bt, min_value(bt), max_value(bt)));  
}  


binary_tree* construct_binary_tree2(char *str, int *pos) {

	bt *btree = NULL; //ponteiro para a arvore
	int i = 0;
	int numInt;       //numero do no (inteiro)
	char numStr[50];  //numero do no (string)
 
	while(str[*pos] == '(') { //ignora os parenteses abrindo
		*pos += 1;
	}

	if(str[*pos] == ')') { //se encontrar parentese fechando, retorna null
		*pos += 1;         // pois o ponteiro eh nulo
		return NULL;
	}
	else {
		while(str[*pos] != '(') {    //se for diferente de abre parenteses
			numStr[i++] = str[*pos]; //le o numero string
			*pos += 1;
		}
		numStr[i] = '\0'; //finalizando a string com '/0'
		numInt = atoi(numStr); //converte o numero string para inteiro

		btree = create_binary_tree(numInt, NULL, NULL); //cria um no com o numero inteiro
		btree->left = construct_binary_tree(str, pos);  //constroi a arvore para o no esquerdo
		btree->right = construct_binary_tree(str, pos); //constroi a arvore para o no direito
	}

	*pos += 1;
	return btree; //retorna o ponteiro para a arvore
} 

bool is_full_binary_tree(binary_tree *bt) { 
  if(bt == NULL) 
    return true; 
  
  if(bt->left == NULL && bt->right == NULL) 
    return true; 
  
  if((bt->left) && (bt->right)) 
    return (is_full_binary_tree(bt->left) && is_full_binary_tree(bt->right)); 
  
return false; 
} 

int main() {
  
  int num, i=0, element, min, max;
  char *string[100];

  binary_tree *bt;

  *string = read_bracket_string();

  bt = construct_btree(*string, &i);


  if(is_BST(bt))
    printf("VERDADEIRO");
  else  
    printf("FALSO");
  
return 0;
}
