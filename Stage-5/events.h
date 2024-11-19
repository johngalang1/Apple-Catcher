#ifndef EVENTS_H
#define EVENTS_H
#include "types.h"
#include "RASTER.H" 
#include "model.h"
#include "renderer.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: events.h
PURPOSE: CONTAINS ALL FUNCTION PROTOTYPES FOR ASYCHRONOUS AND SYNCHRONOUS EVENTS
*/

int check_basket_collision(basket *b, int direction); 

int check_apple_collision(basket *b, apple *a);

void reset_apple_position(apple *a);

void increment_score(score *curr_score);

void decrement_round_timer(timer_round *t);

#endif
