#include "input.h"
#include <osbind.h>   /* For Cconis and Cnecin functions */
#include "model.h"    /* For move_basket and basket struct */

/* Static variable to hold the current basket action */
static BasketAction current_basket_action = BASKET_MOVE_NONE;

/* Initializes the input module */
void input_init() {
    current_basket_action = BASKET_MOVE_NONE;
}

/* Processes keyboard input and sets the current basket action */
void process_basket_input() {
    /* Check if there's any input pending */
    if (Cconis()) {  
        char ch = (char)Cnecin();  /* Read the key if available */

        /* Update current basket action based on the key */
        switch (ch) {
            case 'a':  /* Left key */
                current_basket_action = BASKET_MOVE_LEFT;
                break;
            case 'd':  /* Right key */
                current_basket_action = BASKET_MOVE_RIGHT;
                break;
        }
    }
    /* This is the issue here
    else
    { 
        current_basket_action = BASKET_MOVE_NONE;
    }
    */
}


/* 
 * Moves the basket based on the current basket action.
 * Takes a pointer to a basket object as a parameter and
 * moves it according to the current basket action.
 */
void move_basket_based_on_input(basket *b) {
    /* Determine direction based on the last action */
    int direction = 0;
    process_basket_input();
    if (current_basket_action == BASKET_MOVE_LEFT) {
        direction = -1;
    } else if (current_basket_action == BASKET_MOVE_RIGHT) {
        direction = 1;
    }

    /* Move the basket with the specified direction or stop if no input */
    move_basket(b, direction);
}


/* Returns the current basket action */
BasketAction get_basket_action() {
    return current_basket_action;
}
