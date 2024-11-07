#ifndef INPUT_H
#define INPUT_H

#include "model.h"  /* Include model.h to recognize the basket struct */

typedef enum {
    BASKET_MOVE_NONE,
    BASKET_MOVE_LEFT,
    BASKET_MOVE_RIGHT
} BasketAction;

/* Initializes the input module */
void input_init();

/* Checks if there is input available */
int check_input();

/* Retrieves the next input character */
char get_input();

/* Processes a specific input character */
void process_input(char input, int *quit);

/* Moves the basket based on current input */
void move_basket_based_on_input(basket *b);

/* Returns the current basket action */
BasketAction get_basket_action();

#endif /* INPUT_H */
