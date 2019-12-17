#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _stack stack_t;
typedef struct _node node_t;	

stack_t* newStack();
node_t* newNode(char c);

struct _node {
        char c;
        node_t *next;
};

struct _stack {
        node_t *topo;
        int size;
};

char peek(stack_t * stack) {
	if (stack->size>0) {
		return stack->topo->c;
	}
}

node_t *newNode(char element) {
  node_t *novo  = (node_t *) malloc(sizeof(node_t));
  novo->c = element;
  novo->next = NULL;
return novo;
}

stack_t *newStack() {
  stack_t *novo = (stack_t*) malloc(sizeof(stack_t));
  novo->topo = NULL;
  novo->size = 0;
return novo;
}

void pop_stack(stack_t *stack) {
	if (stack->size >0) {
    node_t *aux = stack->topo;
		stack->topo = stack->topo->next;
		stack->size--;
    free(aux);
	}
}

void clear_stack(stack_t *stack) {
  if (stack->size > 0) {
    pop_stack(stack);
    clear_stack(stack);
  }
}

void insere(stack_t *stack, char element) {
  node_t * aux = newNode(element);
  aux->c = element;
  aux->next = stack->topo;
  stack->topo = aux;
  stack->size++; 
}

void print_stack(stack_t *stack) {
	stack_t *aux = newStack();
	while (stack->size > 0) {
		printf("%c%c",peek(stack),  (stack->size)>1? ' ':'\n' );
		insere(aux,peek(stack));
		pop_stack(stack);	
	}
	while(aux->size > 0) {
		insere(stack,peek(aux));
		pop_stack(aux);

	}

	clear_stack(aux);
  free(aux);
}	

int main()
{	

	stack_t *pilha1 = newStack(); 
	stack_t *pilha2 = newStack(); 
	char c, string[256];
	int num, i, j;

	scanf("%d", &num);

	getchar();

	for(i=0; i< num; i++) {   
    fgets(string, 256, stdin);
    for (j=0; j<strlen(string); j++ ){	
    	switch(string[j]) {
        	
        case '(': 
          insere(pilha1,'(');
          break;
        case ')': 
          if(pilha1->size > 0)
            pop_stack(pilha1);
          else
            insere(pilha1,')'); 
          break;
        case '[': 
          insere(pilha2,'[');
          break;
        case ']': 
          if(pilha2->size > 0)
            pop_stack(pilha2);
          else
            insere(pilha2,']'); 
            break;
      }
    }
       
    if ((pilha1->size == 0 ) && (pilha2->size==0))
    	printf("Yes\n");
  	else
    	printf("No\n");

    clear_stack(pilha1);
    clear_stack(pilha2);
  }
           
return 0;
}