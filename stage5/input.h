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

/* Processes keyboard input and sets the current basket action */
void process_basket_input();

void move_basket_based_on_input(basket *b);

/* Returns the current basket action */
BasketAction get_basket_action();

#endif /* INPUT_H */
