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

int apple_basket_collision(model *curr_model, int i);
int apple_floor_collision(model *curr_model, int i);

void reset_apple_position(apple *a);

void increment_score(model *curr_model);

void decrement_round_timer(UINT16 *base, timer_round *t);

void decrement_start_timer(UINT16 *base, timer_start *t);

int is_start_time_up(timer_start *t);


#endif

