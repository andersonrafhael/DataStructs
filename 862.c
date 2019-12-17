#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _list list_t;
typedef struct _node node_t;

list_t* newList();
node_t* newNode(char value);
void push_back(list_t *list, char value);
void push_front(list_t *list, char value);
void pop_back(list_t *list);
void pop_front(list_t *list);
void prchar(list_t *list);
void destroy(list_t *list);



struct _node {
        char value;
        node_t *next;
};
struct _list {
        node_t *head;
        node_t *tail;
        int size;
};

void destroy(list_t * list)
{
    while (list->size >0)
    {
        pop_front(list);
    }
    free(list);
}

node_t * newNode(char value)
{
        node_t * novo  = (node_t*) malloc(sizeof(node_t));
        novo->value = value;
        novo->next = NULL;
        return novo;

}

list_t * newList()
{
        list_t * novo = (list_t * ) malloc(sizeof(list_t));
        novo-> head = NULL;
        novo->tail = NULL;
        novo->size = 0;
        return novo;

}

void push_front(list_t * list, char value)
{
        node_t * aux = newNode(value);
        aux->value = value;
        aux->next = list->head;
        list->head = aux;


}


void pop_front(list_t *list) {
        

        /*node_t *curr = list->head;
        if(!curr) return;
        curr = curr->next;
        free(list->head);
        list->head = curr;
        --list->size;*/

  node_t * atual = list->head;
  if (atual == NULL)
  {
    return;
  }

list->head = atual->next;
free(atual);
list->size--;

}

void push_back(list_t * list, char value)
{

        node_t * aux = newNode(value);
        if(list->size == 0)
        {
                list->head = list->tail = aux;
        }
        else
        {
                list->tail->next = aux;
                list->tail = aux;
        }
        list->size = list->size +1;
       
}
void print(list_t * list)
{
        node_t * atual = list->head;

        for (;atual != NULL; atual = atual->next)
        {
                printf("%c%c", atual->value, atual->next == NULL? 10:32);
        }
}

void reverseList(list_t * list)
{
        node_t * atual= list->head;
        node_t * anterior = NULL;
        node_t * prox;
        while(atual != NULL)
        {
                prox = atual->next;
                atual->next = anterior;
                anterior = atual;
                atual= prox;

        }
        list->head = anterior;

       
}


void imprimeLimZeros(list_t * list)
{  
        node_t * atual = list->head;
        int intervalos[list->size][2];
        int contadordeIntervalos=0;
        int flag=0,i=0;   // 0 - Buscando o primeiro zero.   1 - Buscando um zero final
        for (i=0;atual != NULL; atual = atual->next,i++)
        {
            if (flag==0)
            {
                if (atual->value == '0')
                 {
                     intervalos[contadordeIntervalos][0] = i;
                      intervalos[contadordeIntervalos][1] = i;
                     flag =1;
                 }
            }
            else
            {
                if(atual->value =='0')
                {
                    intervalos[contadordeIntervalos][1] = i;
                        
                }
                else
                {
                    contadordeIntervalos++;
                    flag=0;

                }
            }
            
        }
        int melhor=0;
        for (i=0; i<=contadordeIntervalos; i++)
        {
            if (  (intervalos[i][1]- intervalos[i][0]) >= (intervalos[melhor][1]- intervalos[melhor][0]))
            {
                melhor=i;
            }
        }
        printf("%d %d", intervalos[melhor][0], intervalos[melhor][1] );
    }


         


int main() {  
        
     list_t * listinha = newList();
     char c;  
     int i=0; 
     while((c=getchar()) != EOF  )
     {      
        if (c=='\n')   
        {
            imprimeLimZeros(listinha);
            destroy(listinha);
            listinha = newList();
            printf("\n");
        }
        else 
        {  
         push_back(listinha,c);
         
        }
     }
     return 0;
}





    




