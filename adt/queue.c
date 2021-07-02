#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* queueInit() {
    Queue *queue = (Queue*) malloc (sizeof(Queue));
    if(queue == NULL) {
        return NULL;
    }

    queue->front = NULL;
    queue->end = NULL;
    queue->size = 0;
    return queue;
}


Node* createNewNode() {
    Node* node_new = (Node*) malloc (sizeof(Node));
    if(node_new == NULL) {
        printf("\nQueue is full.");
    }

    return node_new;
}

int queueIsFull(Node* node) {
    if(node != NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

int enqueue(Queue* queue, queue_data item) {
    if(queueIsEmpty(queue)) {
        queue->front = createNewNode();
        queue->front->data = item;
        queue->end = queue->front;
        ++(queue->size);

        return 1;
    }
    else {
        queue->end->next = createNewNode();
        queue->end->next->data = item;
        queue->end = queue->end->next;
        ++(queue->size);

        return !( queueIsFull(queue->end) );
    }
}


queue_data dequeue(Queue* queue) {
    Node* node_temp;
    queue_data item;

    if(queueIsEmpty(queue)) {
        printf("\ndequeue(...) failed. Queue is empty.");
        exit(-1);
    }
    else if(queue->size == 1) {
        node_temp = queue->front;
        item = queue->front->data;
        queue->front = NULL;
        queue->end = NULL;
        --(queue->size);
        free(node_temp);
        return item;
    }
    else {
        node_temp = queue->front;
        item = queue->front->data;
        queue->front = queue->front->next;
        --(queue->size);
        free(node_temp);
        return item;
    }
}


queue_data queuePeek(Queue* queue) {
    if(queueIsEmpty(queue)) {
        printf("\nqueuePeek(...) failed. Queue is empty. ");
        exit(-1);
    }
    else {
        return queue->front->data;
    }
}


int queueIsEmpty(Queue* queue) {
    return (queue->size == 0 && queue->end == NULL && queue->front == NULL);
}


void queueDelete(Queue* queue) {
    while( !(queueIsEmpty(queue)) ) {
        dequeue(queue);
    }
    free(queue);
    queue = NULL;
}