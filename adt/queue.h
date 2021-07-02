typedef int queue_data; // change this for different data types

typedef struct Node {
    queue_data data;
    struct Node* next;

} Node;

typedef struct Queue {
    Node* front;
    Node* end;
    unsigned short size;
} Queue;

/* queueInit() initializes a queue.
 * Successful function call returns pointer to the queue. Upon failure: returns NULL . */
Queue* queueInit();

/* enqueue(...) adds an item to the end of the queue. 
 * Successful function call returns 1. If queue is full: returns 0. */
int enqueue(Queue* queue, queue_data item);

/* dequeue(...) removes the item from the front of the queue.
 * Successful function call returns the item. Exits upon failure.  */
queue_data dequeue(Queue* queue);

/* queuePeek(...) returns the value of an item in the front of the queue. 
 * Exits upon failure. */
queue_data queuePeek(Queue* q);

/* queueIsEmpty(...) checks if the queue is empty. 
 *Returns 1 if queue is empty, 0 if queue is not empty. */
int queueIsEmpty(Queue* queue);

/* queueDelete(...) deletes the queue. Sets queue pointer to NULL. */
void queueDelete(Queue* queue);