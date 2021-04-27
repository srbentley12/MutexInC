
/* 
 * Author: Steve Bentley
 * Final project for CSC 389
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int mutex = 0;
int state = 0;
int clock = 0;
int queue = 0;
int person_waiting = 0;

int woman_wants_to_enter(){
    if(state == 1){
        printf("Cannot enter, %i male(s) occupies the bathroom.\n", mutex);
        return 0;
    }
    else{
        state = 2;
        mutex++;
        printf("Woman enters bathroom from queue, %i female(s) in bathroom.\n", mutex);
        return 1;
    }
}

int man_wants_to_enter(){
    if(state == 2){
        printf("Cannot enter, %i female(s) occupies the bathroom.\n", mutex);
        return 0;
    }
    else{
        state = 1;
        mutex++;
        printf("Man enters bathroom from queue, %i male(s) in bathroom.\n", mutex);
        return 1;
    }
}

void woman_leaves(){
    mutex--;
    printf("Woman leaves the bathroom, %i female(s) occupies the bathroom\n", mutex);
    if(mutex == 0){
        state = 0;
        printf("The bathroom is empty\n");
    }
    //state_out();
}

void man_leaves(){
    mutex--;
    printf("Man leaves the bathroom, %i male(s) occupies the bathroom\n", mutex);
    if(mutex == 0){
        state = 0;
        printf("The bathroom is empty\n");
    }
    //state_out();
}

void person_wants_to_enter(){
    if(queue == 1){
        printf("Man wants to enter\n");
        if(man_wants_to_enter() == 1){
            dequeue();
        }
    }
    else{
        printf("Woman wants to enter\n");
        if(woman_wants_to_enter() == 1)
            dequeue();
    }
}

void dequeue(){
    queue = (rand() % 2) + 1;
    person_waiting = 0;
}

int queue_is_present(){
    return rand() % 2;
}

int run_clock(int tick){
    if(person_waiting == 0){
        person_waiting = queue_is_present();
        if(person_waiting == 0){
            printf("There is no one waiting\n");
            if(mutex == 0)
                printf("There is no one in the bathroom\n");
            if(mutex > 0 && state == 1)
                printf("There are %i male(s) in the bathroom\n", mutex);
            if(mutex > 0 && state == 2)
                printf("There are %i female(s) in the bathroom\n", mutex);
        }
    }
    if(tick % 4 == 0){
        if(state == 1 && mutex > 0)
            man_leaves();
        if(state == 2 && mutex > 0)
        woman_leaves();
    }
    if(person_waiting == 1){
        gender_queue_out();
        person_wants_to_enter();
    }
    return tick+1;
}

void state_out(){
    if(state == 0)
        printf("Bathroom sign says 'Vacant'\n");
    if(state == 1)
        printf("Bathroom sign says 'Males'\n");
    if(state == 2)
        printf("Bathroom sign says 'Females'\n");
}

void gender_queue_out(){
    if(queue == 1)
        printf("A man is queued next\n");
    if(queue == 2)
        printf("A woman is queued next\n");
}


main() {
    srand(time(0));
    person_waiting = 1;
    printf("\n\n");
    queue = (rand() % 2) + 1;
    
    while(clock < 30){
        printf("Cycle: %i\n", clock);
        state_out();
        clock = run_clock(clock);
        state_out();
        printf("\n");
        //sleep(1);
    }
}

