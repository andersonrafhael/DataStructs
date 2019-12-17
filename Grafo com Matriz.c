#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max_size 1000

bool matriz[max_size][max_size];
int distance[max_size];
int previous[max_size];
int visited[max_size];
int cont=0;

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

void print_list(lista *lista){
  item *atual = lista->head;

  while(atual!= NULL) {
    printf("%d ", atual->valor);
    atual = atual->next;  
  }
}

bool is_empty(lista *queue) {
  if(queue->size == 0)
    return true;
  else
    return false;
}

void bfs(int vert_ini, int vert_dest, int num_vert) {

  lista *fila = create_list();

  int source, i;

  Insere_Fim(fila, vert_ini);
  visited[vert_ini] = 1;
  distance[vert_ini] = 0;

  while(!is_empty(fila)) {
    source = fila->head->valor;
    pop_ini(fila);

    printf("Iniciando busca em largura a partir de %d\n", source);  

    for(i=0; i<num_vert; i++) {
      if(matriz[source][i] && (!visited[i])) {
        Insere_Fim(fila, i);
        visited[i] = 1;
        previous[i] = source;
        distance[i] = distance[source]+1;
        cont++;
      }
    }

  }
}

void verifica_caminho(int vert_origem, int vert_dest) {
  int fim = vert_dest;
  
  if(distance[fim] == -1)
    printf("Sem caminho");
  else if(distance[fim] == distance[vert_origem])
    return;
  else {
    fim = previous[fim];
    verifica_caminho(vert_origem, fim);
    printf("%d => ", fim);
  }
}

void restart_vet() {
  int i;
  for(i=0; i<max_size; i++) {
    distance[i] = -1;
    previous[i] = -1;
    visited[i] = 0;
  }
}


int main() {
  lista *lista1 = create_list();
  int i, j, k, num_vert, num_edge, qtde_testes, vert_origem, vert_dest;

  for(i=0; i<max_size; i++) {
    for(j=0; j<max_size; j++)
        matriz[i][j] = 0;
  }

  scanf("%d %d %d", &num_vert, &num_edge, &qtde_testes);

  for(i=0; i<num_edge; i++) {
    scanf("%d %d", &vert_origem, &vert_dest);
    matriz[vert_origem][vert_dest] = 1;
  }

  for(j=1; j<=qtde_testes; j++) {
    scanf("%d %d", &vert_origem, &vert_dest);
    restart_vet();
    printf("\n--------\n\n");
    printf("Caso de Teste #%d - BFS(%d)\n\n", j, vert_origem);
    bfs(vert_origem, vert_dest, num_vert);

    printf("\n");

    for(i=0; i<num_vert;i++) {
      printf("%d ", i);
      if(distance[i] == -1) 
        printf("| -");
      else    
        printf("| %d", distance[i]);

      if(previous[i] == -1) 
        printf(" | -\n");
      else    
        printf(" | %d\n", previous[i]);
    }
    printf("Caminho entre %d e %d: ", vert_origem, vert_dest);
    verifica_caminho(vert_origem, vert_dest);
    printf("%d\n", vert_dest);
  }

  printf("\n--------");

return 0;
}