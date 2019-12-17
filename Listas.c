#include <stdio.h>
#include <stdlib.h>


typedef struct item {
  int valor;
  struct item *next;
} item;

typedef  struct lista {
  item *head;
  item *tail;
  int size;
} lista;


lista *create_list() {
  lista *novo = (lista *) malloc(sizeof(lista));
  novo->head = NULL;
  novo->tail = NULL;
  novo->size = 0;
return novo;
}

item *novo_item(int valor) {
  item *novo  = (item*) malloc(sizeof(item));
  novo->valor = valor;
  novo->next = NULL;
return novo;
}

void swap(int *num1, int *num2) {
    int aux = *num1;
    *num1 = *num2;
    *num2 = aux;
}

void Insere_Ini(lista *lista, int num) {
  item *novo, *atual;

  novo = novo_item(num);
  novo->next = lista->head;
  if (lista->size == 0) {
    lista->tail = novo;
  }

  lista->head = novo;
  lista->size++;
}

void Insere_Fim(lista *lista, int num) {
  item *atual, *novo, *previous;

  novo = (item *) malloc(sizeof(item));
  novo->valor = num;

  if(lista->size == 0) {
    lista->head = lista->tail = novo;
  }

  else {
    lista->tail->next = novo;
    lista->tail = novo;
  }
  lista->size++;
}

void pop_ini(lista *lista) {
  item *atual;

  atual = lista->head;
  if(!atual) 
    return;
  atual = atual->next;
  free(lista->head);
  lista->head = atual;
  --lista->size;
}

void Insere_Ordena(lista *lista, int num) {
  item *anterior, *atual, *novo;

  novo = novo_item(num);;

  atual = lista->head;
  anterior = NULL;

  if(atual == NULL) { 
    novo->next = NULL;
    lista->head = novo;
  }
  else {
    while (atual != NULL && atual->valor < num){
      anterior = atual;
      atual = atual->next;
    }
  
    novo->next = atual;

    if(anterior == NULL)
      lista->head = novo;
    else
      anterior->next = novo;
  }
  lista->size++;
}

void inverte_lista(lista *lista) {
  item *anterior, *atual, *prox, *aux;

  aux = lista->head;
  anterior = NULL;
  atual = lista->head;

  do {
    prox = atual->next;
    atual->next = anterior;
    anterior = atual;
    atual = prox;
  } while(atual != NULL);

  lista->head = anterior;
}

void print_list(lista *lista){
  item *atual = lista->head;

  while(atual!= NULL) {
    printf("%d ", atual->valor);
    atual = atual->next;  
  }
}

int verifica_listas(lista *lista, int num) {
  item *atual = lista->head;

  while(atual != NULL) {
    if(atual->valor == num) 
      return 1;
    atual = atual->next;
  }
return 0;
}
lista *intersec(lista *lista1, lista *lista2) {
  item *atual1, *atual2;
  lista *intersec = create_list();

  atual1 = lista1->head;
  atual2 = lista2->head;

  while (atual1 != NULL && atual2 != NULL) {
    while (atual1 != NULL && atual2 != NULL) {
      if (atual1->valor == atual2->valor) {
        if (!verifica_listas(intersec, atual1->valor))
          Insere_Fim(intersec, atual2->valor);
      }
    atual2 = atual2->next;
    }  
  atual1=atual1->next;
  atual2=lista2->head; 
  } 

return intersec;
}

int verifica_igual(lista* lista1, lista* lista2 ) {
  item *atual1, *atual2;
  int cont=0;

  atual1 = lista1->head;
  atual2 = lista2->head;

  while (atual1 != NULL && atual2 != NULL) {
    if (atual1->valor == atual2->valor) {
      cont++;
    }
    atual1 = atual1->next;
    atual2 = atual2->next;
  }

return cont;
}


int main(void) {
  lista *lista1 = create_list();
  lista *lista2 = create_list();

  int qtde, i=0, j, num_alunos, nota, aux;

  //printf("Qual o tamanho da 1 lista? ");
  scanf("%d", &qtde);

  for(i=0; i<qtde; i++) {
    scanf("%d", &num_alunos);
    for(j=0; j<num_alunos; j++) {
      scanf("%d", &nota);
      Insere_Fim(lista1, nota);
      Insere_Ordena(lista2, nota);
      }
    aux = verifica_igual(lista1, lista2);
    printf("%d", aux);
    pop_ini(lista1);
    
  }

return 0;
}