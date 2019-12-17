#include <stdio.h>
#include <stdlib.h>

typedef struct element {
  int key;
  int value;
} element;

typedef struct hash_table {
  element *table[20];
  int table_size;
  int qtde;
} hash_table;

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

item *novo_item(int valor) {
  item *novo  = (item*) malloc(sizeof(item));
  novo->valor = valor;
  novo->next = NULL;
return novo;
}

hash_table* create_hash_table(int size) {
  hash_table *htable = (hash_table *) malloc(sizeof(hash_table));
  int i;
  for (i = 0; i < size; i++) 
    htable->table[i] = NULL;
  htable->table_size = size;
  htable->qtde = 0;
return htable;
}

void inserir(hash_table *ht, int key, int value, int size) {
  int h = key % size;
 // while (ht->table[h] != NULL) {
    //if (ht->table[h]->key == key) {
      //ht->table[h]->value = value;
      //break;
    //}
   // h = (h+1) % size;
  //}
  if (ht->table[h] == NULL) {
    element *new_element = (element*) malloc(sizeof(element));
    new_element->key = key;
    new_element->value = value;
    ht->table[h] = new_element;
  }
}

void insert_semcolisao(hash_table *ht, int key, int value, int size) {
  if(ht == NULL || ht->qtde == ht->table_size)
    return;

  int h = key % size;

  if (ht->table[h] == NULL) {
    element *new_element = (element*) malloc(sizeof(element));
    new_element->key = key;
    new_element->value = value;
    ht->table[h] = new_element;
    ht->qtde++;
  }

}

int search_semcolisao(hash_table *ht, int key, int value, int size) {
  if(ht == NULL) 
    return 0;
  int h = key % size; 

  if(ht->table[h] == NULL)
    return 0;
return ht->table[h]->value;
}

void remover(hash_table *ht, int key, int size) {
  int h = key % size;
  while (ht->table[h] != NULL) {
    if (ht->table[h]->key == key) {
      ht->table[h]->key = -1;
    }
    h = (h + 1) % size;
  }
}

void liberaHash(hash_table *ht) {
  if(ht != NULL) {
    int i;
    for(i=0; i < ht->table_size; i++){
      if(ht->table[i] != NULL)
        free(ht->table[i]);
    }
    free(ht->table);
    free(ht);
  }
}

void print_hash(hash_table *ht, int size) {
  int  i, cont = 0;
  for(i=0; i < size; i++) {
    if(ht->table[i] == NULL)    
      printf("\n%d", i); 
    else
      printf("\n%d -> %d", i, ht->table[i]->key);  
    printf(" -> /");
  }
}

int main() {
  
  int qtde_testes, size, qtde_key, i, j, key;

  scanf("%d", &qtde_testes);

  for(i=0; i<qtde_testes; i++) {
    scanf("%d %d", &size, &qtde_key);
    hash_table *ht = create_hash_table(size);

    for(j=0; j<qtde_key; j++) {
      scanf("%d", &key);
      insert_semcolisao(ht, key, j, size);
    }

    print_hash(ht, size);
    printf("\n");
  }

return 0;
}