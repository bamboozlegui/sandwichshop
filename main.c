#include <stdio.h>
#include "sandwich_shop.h"

int main() {

    Sandwich_shop sshop = setShop();
    Stack_holder holder_one = setHolder();
    Stack_holder holder_two = setHolder();

    Queue* qholder_solo = queueInit();
    Queue* qholder_one = queueInit();
    Queue* qholder_two = queueInit();

    Stats s_two;
    s_two.monetary_gain = 0;
    s_two.monetary_loss = 0;
    Stats q_solo;
    q_solo.monetary_gain = 0;
    q_solo.monetary_loss = 0;
    Stats q_two;
    q_two.monetary_gain = 0;
    q_two.monetary_loss = 0;

    // add sandwiches at the start of the day
    addFreshSandwiches_stack(sshop.time_added, sshop.fresh_amount, &holder_one);
    addFreshSandwiches_stack(sshop.time_added, sshop.fresh_amount, &holder_two);
    addFreshSandwiches_queue(sshop.time_added, sshop.fresh_amount, qholder_solo);
    addFreshSandwiches_queue(sshop.time_added, sshop.fresh_amount, qholder_one);
    addFreshSandwiches_queue(sshop.time_added, sshop.fresh_amount, qholder_two);

    sshop.time_added = 0;

    // start selling
    for(int i = 0; i < (sshop.day_length * 60); ++i)
    {
        if( (i != 0) && (i % (sshop.delivery_period * 60) == 0) )
        {
            // stack holders
            if(holder_two.amount >= holder_one.amount)
            {
                addFreshSandwiches_stack(sshop.time_added, sshop.fresh_amount, &holder_one);
            }
            else
            {
                addFreshSandwiches_stack(sshop.time_added, sshop.fresh_amount, &holder_two);
            }
            // queue holders
            if(qholder_two->size >= qholder_one->size)
            {
                addFreshSandwiches_queue(sshop.time_added, sshop.fresh_amount, qholder_one);
            }
            else
            {
                addFreshSandwiches_queue(sshop.time_added, sshop.fresh_amount, qholder_two);
            }
            addFreshSandwiches_queue(sshop.time_added, sshop.fresh_amount, qholder_solo);

        }
        // check if customer buys a sandwich
        if(checkProb(sshop.prob_of_sale) == 1) 
        {
            if(checkProb(0.5) == 1)
            {
                // stack holders
                if(checkIfEmpty(holder_one.stack) != 1)
                {
                    serveSandwich(&holder_one, &(s_two.monetary_gain), sshop.cost);
                }
                else if(checkIfEmpty(holder_two.stack) != 1) 
                {
                    serveSandwich(&holder_two, &(s_two.monetary_gain), sshop.cost);
                }

                // queue holders
                if(queueIsEmpty(qholder_one) != 1)
                {
                    dequeue(qholder_one);
                    q_two.monetary_gain += sshop.cost;
                }
                else if(queueIsEmpty(qholder_two) != 1)
                {
                    dequeue(qholder_two);
                    q_two.monetary_gain += sshop.cost;
                }
            }
            else 
            {
                if(checkIfEmpty(holder_two.stack) != 1) 
                {
                    serveSandwich(&holder_two, &(s_two.monetary_gain), sshop.cost);
                }
                else if(checkIfEmpty(holder_one.stack) != 1) 
                {
                    serveSandwich(&holder_one, &(s_two.monetary_gain), sshop.cost);
                }

                if(queueIsEmpty(qholder_two) != 1)
                {
                    dequeue(qholder_two);
                    q_two.monetary_gain += sshop.cost;
                }
                else if(queueIsEmpty(qholder_one) != 1)
                {
                    dequeue(qholder_one);
                    q_two.monetary_gain += sshop.cost;
                }
            }
            if(queueIsEmpty(qholder_solo) != 1)
            {
                dequeue(qholder_solo);
                q_solo.monetary_gain += sshop.cost;
            }
        }
        ++(sshop.time_added);
    }


    // check for old sandwiches in stack holders
    checkForOldSandwiches_stack(holder_one.stack, ((sshop.day_length - sshop.fresh_time) * 60), &s_two.monetary_loss, sshop.cost);
    checkForOldSandwiches_stack(holder_two.stack, ((sshop.day_length - sshop.fresh_time) * 60), &s_two.monetary_loss, sshop.cost);

    checkForOldSandwiches_queue(qholder_solo, ((sshop.day_length - sshop.fresh_time) * 60), &q_solo.monetary_loss, sshop.cost);
    checkForOldSandwiches_queue(qholder_one, ((sshop.day_length - sshop.fresh_time) * 60), &q_two.monetary_loss, sshop.cost);
    checkForOldSandwiches_queue(qholder_two, ((sshop.day_length - sshop.fresh_time) * 60), &q_two.monetary_loss, sshop.cost);

    printf("Two stack holders:\nmonetary gain: %g\nmonetary loss: %g\nprofit: %g\n\n", s_two.monetary_gain, s_two.monetary_loss, s_two.monetary_gain - s_two.monetary_loss);
    printf("One queue holder:\nmonetary gain: %g\nmonetary loss: %g\nprofit: %g\n\n", q_solo.monetary_gain, q_solo.monetary_loss, q_solo.monetary_gain - q_solo.monetary_loss);
    printf("Two queue holders:\nmonetary gain: %g\nmonetary loss: %g\nprofit: %g\n\n", q_two.monetary_gain, q_two.monetary_loss, q_two.monetary_gain - q_two.monetary_loss);

    return 0;
}