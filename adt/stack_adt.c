#include<stdio.h>
#include<stdlib.h>
#include "stack_adt.h"


void push(int data, struct node** stack)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode -> data = data;
    if(*stack == NULL)
        newNode -> size1 = 1;
    else
        newNode -> size1 = ((*stack) -> size1) + 1;

    newNode -> next = *stack;
    (*stack) = newNode;
}

int pop(struct node** stack)
{
    if(*stack != NULL)
    {
        struct node* tempPtr = *stack;
        int poppedElement = tempPtr -> data;
        *stack = (*stack) -> next;
        free(tempPtr);
        return poppedElement;
    }
    else
    {
        printf("Cannot pop from an empty stack");
        exit(1);
    }

}

int top(struct node* stack)
{
    if(stack != NULL)
        return stack -> data;
    else
    {
        printf("Cannot get top from an empty stack");
        exit(1);
    }
}

int checkIfEmpty(struct node* stack)
{
    if(stack == NULL)
        return 1;
    else
        return 0;
}

int stackSize(struct node* stack)
{
    if(stack == NULL)
        return 0;
    else
        return stack -> size1;
}
