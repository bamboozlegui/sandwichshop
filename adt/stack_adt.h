#ifndef STACKHEADER_H_INCLUDED
#define STACKHEADER_H_INCLUDED

typedef struct node
{
    int data;
    int size1;
    struct node* next;
} node;
void push(int data, struct node** stack);
int pop(struct node** stack);
int top(struct node* stack);
int checkIfEmpty(struct node* stack);
int stackSize(struct node* stack);

#endif // STACKHEADER_H_INCLUDED
