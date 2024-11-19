#ifndef INPUT_H
#define INPUT_H
#include "model.h"  

/* 
AUTHORS: John G, Zach L
FILE NAME: input.h
PURPOSE: CONTAINS ALL FUNCTION PROTOTYPES FOR INPUT FUNCTIONS
*/

typedef enum {
    BASKET_MOVE_NONE,
    BASKET_MOVE_LEFT,
    BASKET_MOVE_RIGHT
} BasketAction;

void input_init();

int check_input();

char get_input();

void process_input(char input, int *quit);

void move_basket_based_on_input(basket *b);

BasketAction get_basket_action();

#endif 
