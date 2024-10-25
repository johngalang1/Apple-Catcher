#ifndef DRIVER_H
#define DRIVER_H

#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include <osbind.h>

/* Function prototypes for testing */

/* Test basket movement */
void test_basket_movement(void);

/* Test apple collision with the basket */
void test_apple_collision(void);

/* Test random apple position generation */
void test_random_apple_position(void);

/* Test basket collision with the right border */
void test_basket_right_border_collision(void);

/* Test basket collision with the left border */
void test_basket_left_border_collision(void);

/* Test apple movement */
void test_apple_movement(void);

/* Test score increment */
void test_score_increment(void);

/* Test timer decrement */
void test_timer_decrement(void);

/* Test display message */
void test_display_message(void);

#endif /* DRIVER_H */
