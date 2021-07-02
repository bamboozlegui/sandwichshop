#include "stack_adt.h"
#include "queue.h"

typedef struct Sandwich_shop {
    double prob_of_sale;
    int fresh_amount;
    int delivery_period;
    int fresh_time;
    int day_length;
    int time_added;
    double cost;
} Sandwich_shop;

typedef struct Stack_sandwich_holder {
    int amount;
    node* stack;
} Stack_holder;

typedef struct Statistics {
    double monetary_gain;
    double monetary_loss;
    double profit;
} Stats;

void addFreshSandwiches_stack(int time_added, int fresh_amount, Stack_holder* holder_one);
void checkForOldSandwiches_stack(node* holder, int time_fresh, double *loss, double cost);
void addFreshSandwiches_queue(int time_added, int fresh_amount, Queue* qholder);
void checkForOldSandwiches_queue(Queue* holder, int time_fresh, double *loss, double cost);
void serveSandwich(Stack_holder* holder, double* budget, double sandwich_cost);
int checkProb(double probability);
Sandwich_shop setShop();
Stack_holder setHolder();