#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#define max_size 256

typedef unsigned char byte;

typedef struct huffman_tree {
    int frequency;
    byte character;
    struct huffman_tree *left;
    struct huffman_tree *right;
} huffman_tree;

typedef struct min_heap {
    int size;
    int capacity;
    struct huffman_tree **vet;
} min_heap;


// cria um huffman_node
huffman_tree *create_huff_node(byte character, int frequency) {
    huffman_tree *new_huff_node = (huffman_tree *) malloc(sizeof(huffman_tree));
    if (new_huff_node) {
        new_huff_node->character = character;
        new_huff_node->frequency = frequency;
        new_huff_node->left = NULL;
        new_huff_node->right = NULL;
    }
return new_huff_node;
}

// cria uma min_heap
min_heap *create_heap() {
    min_heap *hp = (min_heap*) malloc(sizeof(min_heap));

    hp->size = 0;
    hp->capacity = max_size;
    hp->vet = (huffman_tree**) malloc(max_size * sizeof(huffman_tree*));

return hp;
}
 
// libera um huff_node da memória
void free_ht(huffman_tree *ht) {
    if (ht) {
        free_ht(ht->left);
        free_ht(ht->right);
        free(ht);
    }
}

// retorna o caracter a partir de uma posição da min heap
int item_of(min_heap *heap, int i) {
return heap->vet[i]->character;
}

// troca 2 huff_nodes de posição
void swap_heap_node(huffman_tree **a, huffman_tree **b) {
    huffman_tree *aux = *a;
    *a = *b;
    *b = aux;
}

// troca 2 inteiros de posição
void swap(int *num1, int *num2) {
    int aux = *num1;
    *num1 = *num2;
    *num2 = aux;
}

// verifica se a min heap está vazia
bool is_empty(min_heap *hp) {
  if(hp->size == 0)
    return true;
  else
    return false;
}

// Verifica se a heap possui apenas um elemento
int is_unique(min_heap *heap)  { 
	return (heap->size == 1); 
} 

// retorna o maior valor entre 2 dados
unsigned int max_value(unsigned int num1, unsigned int num2) {
    return num1 > num2 ? num1 : num2;
}

// aux_function para o pegar o pai
int get_parent_index(min_heap *heap, int i) {
return i>>1;
}

// aux_function para o pegar o vizinho da esquerda

int get_left_index(min_heap *heap, int i) {
return (i<<1) + 1;
}

// aux_function para o pegar o vizinho da direita
int get_right_index(min_heap *heap, int i) {
return (i<<1) + 2;
}


// função min_heap
void min_heapify(min_heap *heap, int i) {
  int smallest;
  int left_index = get_left_index(heap, i);
  int right_index = get_right_index(heap, i);

  if (left_index <= heap->size &&
    heap->vet[left_index]->frequency < heap->vet[i]->frequency) {
    smallest = left_index;
  } 
  else 
    smallest = i;
  
  if (right_index <= heap->size && 
  heap->vet[right_index]->frequency < heap->vet[smallest]->frequency) 
    smallest = right_index;
  
  if (smallest != i) {
    swap_heap_node(&heap->vet[i], &heap->vet[smallest]);
    min_heapify(heap, smallest);
  }
}

// utiliza a função acima para criar um min_heap
void build_min_heap(min_heap *hp) {
    int i;
    for(i=hp->size/2; i>=1; i--) 
        min_heapify(hp, i);
}

// Função para criar e construir a heap
//min_heap *Create_Build_Heap(byte character, int frequency){
 // min_heap *heap = create_heap();


//}

// insere na min heap
void insert_heap(min_heap *hp, huffman_tree *ht) {
    if(hp->size >= max_size)
        printf("Heap Overflow");
    else {
      ++hp->size;
      int key_index = hp->size;
      int parent_index = get_parent_index(hp, key_index);

      while(key_index >= 1 && ht->frequency < hp->vet[parent_index]->frequency) {
        key_index = parent_index;
      }

      hp->vet[key_index] = ht;       
    }
}

// Função que retorna o menor valor da heap
huffman_tree *return_min_heap(min_heap * heap) {
  huffman_tree *aux = heap->vet[0];
  heap->vet[0] = heap->vet[heap->size-1];

  heap->size--;
  min_heapify(heap, 0);

return aux; 
}

// Verifica se o nó é uma folha
int isLeaf(huffman_tree *root) { 

	return !(root->left) && !(root->right); 
} 

void print_heap(min_heap *hp){
  int size = hp->size;
  int i;
  for (i=1; i<=size; i++) {
    if(i==size)
        printf("%d", hp->vet[i]->character);
    else
        printf("%d | ", hp->vet[i]->character);
  }
  printf("\n");
}




int main() {
  
    min_heap *heap = create_heap();
    //char string[INT_MAX];
    int pos[max_size], i;
    byte character;
    byte name_file[] = "aaa.txt"; //nome do arquivo de texto a ser lido

    FILE *arq;
	arq = fopen(name_file, "rb"); //abre o arquivo para leitura

    memset(pos, 0, sizeof(pos));

    while((character = fgetc(arq)) != (byte)EOF) {
	    pos[character]++;
	}

    for(i=max_size-1; i>=0; i--) {
        if(pos[i] != 0) {
          huffman_tree *huffnode = create_huff_node((byte) i, pos[i]);
          insert_heap(heap, huffnode);
        }
    }

    build_min_heap(heap);
    print_heap(heap);



fclose(arq); //fecha o arquivo
    
return 0;
}