#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_SIZE 30

typedef struct list {
  int item;
  struct list *next;
} list;

typedef struct grafo {
  list *vertice[MAX_SIZE];
  short visited[MAX_SIZE];
  int *grau;
} grafo;

typedef struct queue {
  int size;
  int head;
  int tail;
  int items[MAX_SIZE];
} fila;

grafo* create_graph() {
  grafo *graph = (grafo*) malloc(sizeof(grafo));
  int i;
  for (i = 1; i <= MAX_SIZE - 1; i++) {
    graph->vertice[i] = NULL;
    graph->visited[i] = 0;
  }
return graph;
}

list *create_list(int item) {
  list *new_list = (list*) malloc(sizeof(list));
  new_list->item = item;
  new_list->next = NULL;
return new_list;
}

fila *create_queue() {
  fila *nova_fila = (fila*) malloc(sizeof(fila));
  nova_fila->size = 0;
  nova_fila->head = 0;
  nova_fila->tail = MAX_SIZE-1;
return nova_fila;
}

bool is_empty(fila *queue) {
  if(queue->size == 0)
    return true;
  else
    return false;
}

void enqueue(fila *queue, int item) {
  if(queue->size >= MAX_SIZE) {
    printf("Queue overflow");
  } 
  else {
    queue->tail = (queue->tail + 1) % MAX_SIZE;
    queue->items[queue->tail] = item;
    queue->size++;
  }
}

int dequeue(fila *queue) {
  if(is_empty(queue)) {
    printf("Queue underflow");
    return -1;
  } 
  else {
    int dequeued = queue->items[queue->head];
    queue->head = (queue->head + 1) % MAX_SIZE;
    queue->size--;
    return dequeued;
  }
}

void insert_edge(grafo *graph, int vert1, int vert2) {
  list *vertex;
  vertex = create_list(vert1);
  vertex->next = graph->vertice[vert2];
  graph->vertice[vert2] = vertex;

  vertex = create_list(vert2);
 vertex->next = graph->vertice[vert1];
  graph->vertice[vert1] = vertex;
}

void dfs(grafo *graph, int source) {
  graph->visited[source] = 1;
  printf("%d\n", source);
  list *adj_list = graph->vertice[source];
  while (adj_list != NULL) {
    if(!graph->visited[adj_list->item]) 
      dfs(graph, adj_list->item);
    
    adj_list = adj_list->next;
  }
}

void bfs(grafo *graph, int source) {
  fila *fila = create_queue();
  
  int dequeued;
  
  list * adj_list = graph->vertice[source];
  graph->visited[source] = 1;
  printf("%d\n", source);

  enqueue(fila, source);

  while (!is_empty(fila)) {
    dequeued = dequeue(fila);
    adj_list = graph->vertice[dequeued];
    while (adj_list != NULL) {
      if (!graph->visited[adj_list->item]) {
        printf("%d\n", adj_list->item);
        graph->visited[adj_list->item] = 1;
        enqueue(fila, adj_list->item);
      }
      adj_list = adj_list->next;
    }
  }
}

void print_graph(grafo *graph){
  int i; 
  list *aux, *aux2;
  for(i=1; i<MAX_SIZE-1; i++) {
    aux = graph->vertice[i];
    printf("%d => ", i);
   while(aux->next != NULL) {
     aux2 = aux->next;
     if(aux2->next == NULL)
        printf("%d", aux->item);
      else  
        printf("%d => ", aux->item);
      aux = aux->next;
    } 
  printf("\n");
  }
}


int main(void) {

  int num_vert, num_edge, v_origem, v_destino;

  grafo *grafo = create_graph();

  insert_edge(grafo, 0, 1);
  insert_edge(grafo, 1, 3);
  insert_edge(grafo, 1, 2);
  insert_edge(grafo, 2, 4);
  insert_edge(grafo, 3, 0);
  insert_edge(grafo, 3, 4);
  insert_edge(grafo, 4, 1);

  bfs(grafo, 4);
  printf("\n");
  print_graph(grafo);

return 0;
}