#ifndef EVENTS_H
#define EVENTS_H
#include "types.h"
#include "RASTER.H" 
#include "model.h"
#include "renderer.h"


int check_basket_collision(basket *b, int direction); 

int check_apple_collision(basket *b, apple *a);

void reset_apple_position(apple *a);

void increment_score(score *curr_score);

void decrement_round_timer(UINT16 *base, timer_round *t);

int is_start_time_up(timer_start *t);

/* Message Functions */ 
void display_message(message *msg);
void clear_message(message *msg);

#endif
