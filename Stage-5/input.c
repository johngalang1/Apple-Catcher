#include "input.h"
#include <osbind.h>   
#include "model.h"   

/* 
AUTHORS: John G, Zach L
FILE NAME: input.c
PURPOSE: CONTAINS ALL FUNCTIONS CONTROLLING INPUT FOR THE BASKET
*/

/* Static variable to hold the current basket action */
static BasketAction current_basket_action = BASKET_MOVE_NONE;

void input_init() {
    current_basket_action = BASKET_MOVE_NONE;
}

/* Checks if there is input available */
int check_input() {
    return Cconis(); 
}

/* Retrieves the next input character from the keyboard buffer */
char get_input() {
    return (char)Cnecin(); 
}

/* Processes a specific input character */
void process_input(char input, int *quit) {
    switch (input) {
        case 'a':  /* Left key */
            current_basket_action = BASKET_MOVE_LEFT;
            break;
        case 'd':  /* Right key */
            current_basket_action = BASKET_MOVE_RIGHT;
            break;
        case 'q':  
        case 'Q':
            *quit = 1;  
            break;
        default:
            current_basket_action = BASKET_MOVE_NONE;
            break;
    }
}

/* Moves the basket based on the current basket action */
void move_basket_based_on_input(basket *b) {
    int direction = 0;
    if (current_basket_action == BASKET_MOVE_LEFT) {
        direction = -1;
    } else if (current_basket_action == BASKET_MOVE_RIGHT) {
        direction = 1;
    }

    move_basket(b, direction);
}

/* Returns the current basket action */
BasketAction get_basket_action() {
    return current_basket_action;
}
