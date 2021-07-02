#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sandwich_shop.h"

void readParams(Sandwich_shop* shop, char file_name[]) 
{
    FILE* data = fopen(file_name, "r");
    fscanf(data, "%lf %d %d %d %lf %d", &shop->prob_of_sale, &shop->fresh_amount, &shop->delivery_period, &shop->fresh_time, &shop->cost, &shop->day_length);
    fclose(data);
}

void addFreshSandwiches_stack(int time_added, int fresh_amount, Stack_holder* holder) {
    
    for (int i = 0; i < fresh_amount; ++i)
    {
        push(time_added, &(holder->stack));
        ++(holder->amount);
    }
}

void addFreshSandwiches_queue(int time_added, int fresh_amount, Queue* qholder) 
{
    for(int i = 0; i < fresh_amount; ++i)
    {
        enqueue(qholder, time_added);
    }
}

void serveSandwich(Stack_holder* holder, double* profit, double sandwich_cost) {
    if(checkIfEmpty(holder->stack) != 1) 
    {
        pop(&(holder->stack));
        holder->amount -= sandwich_cost;
        *profit += sandwich_cost;
    }
}

void checkForOldSandwiches_stack(node* holder, int time_fresh, double *loss, double cost) 
{
    int time_added;
    while(checkIfEmpty(holder) != 1) 
    {
        time_added = pop(&holder);
        if(time_fresh >= time_added) 
        {
            *loss += cost;
        }
    }
}

void checkForOldSandwiches_queue(Queue* holder, int time_fresh, double *loss, double cost) 
{
    int time_added;
    while(queueIsEmpty(holder) != 1) 
    {
        time_added = dequeue(holder);
        if(time_fresh >= time_added) 
        {
            *loss += cost;
        }
    }
}

int checkProb(double probability) 
{
    return (((double)rand() / (double)RAND_MAX) <= probability);
}

Sandwich_shop setShop() {
    Sandwich_shop sshop;
    char FILE_NAME[] = "data.txt";
    readParams(&sshop, FILE_NAME);
    sshop.time_added = 0;
    srand(time(NULL));
    return sshop;
}

Stack_holder setHolder() {
    Stack_holder holder;
    holder.stack = NULL;
    holder.amount = 0;
    return holder;
}