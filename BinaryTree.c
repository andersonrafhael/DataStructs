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
    if(vetor_ordenacao[i]<=vetor_ordenacao[i+1])
      continue;
    else
      return 1;
  }
return 0;
}

bool is_bst(binary_tree *bt) { 
  binary_tree *prev = NULL; 
  
  if(bt) { 
    if (!is_bst(bt->left)) 
      return false; 
   
    if (prev != NULL && bt->item <= prev->item) 
      return false; 
  
    prev = bt; 
  
    return is_bst(bt->right); 
  } 
return true; 
} 

int findIndex(char *string, int index_ini, int index_fim) { 
    if (index_ini > index_fim) 
        return -1; 
  
    // Inbuilt stack 
    stack<char> s; 
  
    for (int i = index_ini; i <= index_fim; i++) { 
  
        // if open parenthesis, push it 
        if (string[i] == '(') 
            s.push(string[i]); 
  
        // if close parenthesis 
        else if (string[i] == ')') { 
            if (s.top() == '(') { 
                s.pop(); 
  
                // if stack is empty, this is  
                // the required index 
                if (s.empty()) 
                    return i; 
            } 
        } 
    } 
    // if not found return -1 
    return -1; 
} 
  
// function to construct tree from string 
binary_tree *treeFromString(char *string, int index_ini, int index_fim) { 
    
  if (index_ini > index_fim) 
    return NULL; 
  
  binary_tree *raiz = create_binary_tree(string[index_ini] - '0', NULL, NULL); 
  int index = -1; 
  
  if (index_ini + 1 <= index_fim && string[index_ini + 1] == '(') 
      index = findIndex(string, index_ini + 1, index_fim); 
  
  if (index != -1) { 
    raiz->left = treeFromString(string, index_ini + 2, index - 1); 
    raiz->right = treeFromString(string, index + 2, index_fim - 1); 
  } 

return raiz; 
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
    printf("      %d ", bt->item);
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

int main() {
  
  int num;

  binary_tree *bt = create_empty_bt();


return 0;
}
