#ifndef EVENTS_H
#define EVENTS_H
#include "types.h"
#include "RASTER.H" 
#include "model.h"


void check_basket_collision(basket *b); 

void check_apple_collision(UINT32 *base, basket *b, apple *a, score *game_score);

void reset_apple(apple *a); 

void update_score(UINT16 *base, score *curr_score); 
void increment_score(UINT16 *base, score *curr_score);

void update_round_timer(UINT16 *base, timer_round *t); 
void decrement_start_timer(timer_start *t);

timer_start *init_start_timer();
int is_start_time_up(timer_start *t);

/* Message Functions */ 
void display_message(message *msg);
void clear_message(message *msg);

#endif
