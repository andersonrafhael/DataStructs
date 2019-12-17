#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"


typedef unsigned char byte;

typedef struct b_tree{
    void *c;        //-> void* c
    long long int freq;
    struct b_tree *next;
    struct b_tree *left;
    struct b_tree *right;

} BinaryTree;

//elementos da hash sao vetores que armazenama ate 8bits
typedef struct element {
	byte binary[8];
} element;

//estrutura hash com no máximo 256 elementos
typedef struct hashtable{
	struct element *table[256];
} hash;

//cria uma tabela hash
hash* createTable() {
	hash *new_hash = (hash*) malloc(sizeof(hash));
    int i;
    for(i=0;i<256;i++){
        new_hash->table[i]=NULL;
    }
	return new_hash; 
}
//adiciona elementos na hash
void put_in_hash(hash *hashtable, byte key, byte binary[], int pos){
    int i;
    element *new_element = (element*)malloc(sizeof(element));
    for(i=0;i<pos;i++){
        new_element->binary[i]=binary[i];
    }
    hashtable->table[key]=new_element;
}

//imprime tabela hash
void print_hash(hash *hashtable){
  int i;
  for(i=0;i<256;i++){
      if(hashtable->table[i] != NULL){
        printf("%c: %s", i, hashtable->table[i]->binary);
        printf("\n"); 
      }
  	}
}

BinaryTree *head = NULL;

BinaryTree* createEmpty(){
    return NULL;
}

int isEmpty(BinaryTree *bt){
    return (bt != NULL);
}

BinaryTree* createQueue(void *c, long long int freq, BinaryTree *bt, BinaryTree *left, BinaryTree *right){
    BinaryTree *new_bt = (BinaryTree*) malloc(sizeof(BinaryTree));
    new_bt->c = c;
    new_bt->freq = freq;
    new_bt->left = left;
    new_bt->right = right;
    new_bt->next = NULL;

    if(bt == NULL){
        head = new_bt;
    }else {
        BinaryTree *current = bt, *prev = NULL;
        while(current != NULL && current->freq < new_bt->freq){
            prev = current;
            current = current->next;
        }
        if(prev == NULL){
            new_bt->next = current;
            head = new_bt;
        } else if(prev != NULL){
            prev->next = new_bt;
            new_bt->next = current;
        }
    }
    return head;
}

BinaryTree* getLeft(BinaryTree *bt){
    return bt->left;
}

BinaryTree* getRight(BinaryTree *bt){
    return bt->right;
}

void* getValue(BinaryTree *bt){
    return bt->c;
}

BinaryTree* getNext(BinaryTree *bt){
    return bt->next;
}

long long int getFreq(BinaryTree *bt){
    return bt->freq;
}

BinaryTree* removeNode(BinaryTree *bt){
    BinaryTree *tmp = bt;
    bt = bt->next;
    head = bt;
    tmp->next = NULL;
    return bt;
}

int size = 0;

int sizeTree(BinaryTree *bt)  {
    if(isEmpty(bt)){
        if(bt->left == NULL && bt->right == NULL){
            if( (*(char*)(bt->c) == '*') || (*(char*)(bt->c) == '\\') ){
                size++;
            }
        }
        size++;
        sizeTree(bt->left);
        sizeTree(bt->right);
    }
    return size;
}

void printPreOrder(BinaryTree *bt, FILE *file)  {
    if(isEmpty(bt)){
        if(bt->left == NULL && bt->right == NULL){
            if(*(unsigned char*)(bt->c) == '*'){
                fprintf(file,"\\%c", *(unsigned char*)(bt->c));
            }
            else if(*(unsigned char*)(bt->c) == '\\') {
                fprintf(file, "\\%c", *(unsigned char*)(bt->c));
            } else fprintf(file, "%c", *(unsigned char*)(bt->c));

        } else fprintf(file, "%c", *(unsigned char*)(bt->c));

        printPreOrder(bt->left,file);
        printPreOrder(bt->right,file);
    }
}

BinaryTree* createBinaryTree(void *item, BinaryTree *left, BinaryTree *right){
    BinaryTree *new_bt = (BinaryTree*) malloc(sizeof(BinaryTree));
    new_bt->c = item;
    new_bt->left = left;
    new_bt->right = right;
    return new_bt;
}

int pos = 0;

BinaryTree* rebuildTree(BinaryTree *bt, char *tree, int size){
    if(tree[pos] != '*'){
        if(tree[pos] == '\\') pos++;
        void *item = &tree[pos];
        bt = createBinaryTree(item, NULL, NULL);
        return bt;
    }
        void *item = &tree[pos];
        bt = createBinaryTree(item, NULL, NULL);
        pos++;

        bt->left = rebuildTree(bt->left, tree, size);
        pos++;
        bt->right = rebuildTree(bt->right, tree, size);

    return bt;
}

BinaryTree *bt;

int init_suite1(void) {
    return 0;
}

int clean_suite1(void) {
    return 0;
}

void testCreateNode(){
    bt = createEmpty();
    if(bt == NULL){
        CU_ASSERT(1);
    }
}

void testCreateQueue() {
    unsigned char *item = (unsigned char*) malloc(sizeof(unsigned char));
    int s[6] = {1,4,3,6,5,2};
    
    int i;
    for(i = 0; i < 6; i++){
        *item = (unsigned char)i;
        bt = createQueue(item, s[i], bt, NULL, NULL);
    }
    if(bt != NULL){
        CU_ASSERT(1);
    }
}

void testGet(){
    BinaryTree *cur = bt;
    int i;
    for(i = 0; i < 6; i++){
        if(getFreq(cur) != (i+1)){
            break;
        }
        cur = getNext(cur);
    }
    if(i != 6){
        CU_ASSERT(0);
    }
}

void testRemoveNode() {
    while(bt != NULL){
        bt = removeNode(bt);
    }
    if(bt == NULL){
        CU_ASSERT(1);
    }
}

int i=0;

void testHash() {
    hash *ht = createTable();

    // Teste para a criação da hash
    for(i=0; i<256; i++) {
        if(ht->table[i] == NULL)
            CU_ASSERT(1);
    }

    // Teste para inserção na hash
    byte bin[5] = "0101";
    bin1[5] = '0111', bin2[5] = '0001';
    put_in_hash(ht, 'a', bin, 0);
    CU_ASSERT_STRING_EQUAL(ht->table['a']->binary, bin);

    put_in_hash(ht, 'b', bin1, 1);
    CU_ASSERT_STRING_EQUAL(ht->table['a']->binary, bin1);

    put_in_hash(ht, 'c', bin2, 2);
    CU_ASSERT_STRING_EQUAL(ht->table['c']->binary, bin2);

}

int main(){
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
       return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
       CU_cleanup_registry();
       return CU_get_error();
   }
   /* add the tests to the suite */
   if ((NULL == CU_add_test(pSuite, "Test of createNode: ", testCreateNode)) ||
       (NULL == CU_add_test(pSuite, "Test of createQueue: ", testCreateQueue)) ||
       (NULL == CU_add_test(pSuite, "Test of getFreq: ", testGet)) ||
       (NULL == CU_add_test(pSuite, "Test of removeNode: ", testRemoveNode)) ||
       (NULL == CU_add_test(pSuite, "Test of Hash", testHash))  ) {
       CU_cleanup_registry();
       return CU_get_error();
   }
//FIM SUITE1

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}