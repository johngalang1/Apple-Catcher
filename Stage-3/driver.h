#ifndef DRIVER_H
#define DRIVER_H
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include <osbind.h>


/* 
AUTHORS: John G, Zach L
FILE NAME: driver.h
PURPOSE: CONTAINS ALL FUNCTION PROTOTYPES FOR TESTING
*/
void test_basket_movement(void);

void test_apple_collision(void);

void test_random_apple_position(void);

void test_basket_right_border_collision(void);

void test_basket_left_border_collision(void);

void test_apple_movement(void);

void test_score_increment(void);

void test_timer_decrement(void);

void test_display_message(void);

#endif 
