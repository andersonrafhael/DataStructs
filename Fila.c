#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10

typedef struct queue {
  int current_size;
  int head;
  int tail;
  int items[MAX_QUEUE_SIZE];
} queue;

queue* create_queue() {
  queue *new_queue = (queue*) malloc(sizeof(queue));
  new_queue->current_size = 0;
  new_queue->head = 0;
  new_queue->tail = MAX_QUEUE_SIZE – 1;
  return new_queue;
}

void enqueue(queue *queue, int item) {
  if (queue->current_size >= MAX_QUEUE_SIZE) {
    printf("Queue overflow");
  } 
  else {
    queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
    queue->items[queue->tail] = item;
    queue->current_size++;
  }
}

int dequeue(queue *queue) {
  if (is_empty(queue)) {
    printf("Queue underflow");
    return -1;
  }
  else {
    int dequeued = queue->items[queue->head];
    queue->head = (queue->head + 1) % MAX_QUEUE_SIZE;
    queue->current_size--;
    return dequeued;
  }
}