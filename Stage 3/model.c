#include "model.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: model.h
PURPOSE: CONTAINS FUNCTIONS FOR OBJECT BEHAVIOURS FOR THE GAME
*/

/* 
NAME: 
PARAMETERS: 
PURPOSE: 
DETAILS:
*/
void move_basket(basket *b, int direction)
{
    /* Update the basket's horizontal position based on direction */
    b->x += direction * b->delta_x;

    /* Ensure the basket does not move beyond the left boundary (x = 0) */
    if (b->x < 0) 
    {
        b->x = 0;  /* Stop at the left boundary */
    }

    /* Ensure the basket does not move beyond the right boundary */
    if (b->x > (SCREEN_WIDTH - 64)) 
    {
        b->x = SCREEN_WIDTH - 64;  /* Stop at the right boundary */
    }
}

/* score functions */

score *init_score()
{
    static score game_score;
        game_score.digit1_x = 32; /* ones digit */
        game_score.digit1_y = 16;
        game_score.digit2_x = 16; /* tens digit */
        game_score.digit2_y = 16;
        game_score.height = CHARACTER_HEIGHT;
        game_score.value = 0;
    return &game_score;
}

void increment_score(UINT16 *base, score *curr_score)
{
 
    curr_score->value += 1;
    update_score(base, curr_score);
}

/* round timer functions */

timer_round *init_round_timer()
{
    static timer_round t;
        t.digit1_x = 608; /* ones digit */
        t.digit1_y = 16;
        t.digit2_x = 592; /* tens digit */
        t.digit2_y = 16;
        t.height = CHARACTER_HEIGHT;
        t.value = 60; 
    return &t;
}

void decrement_round_timer(UINT16 *base, timer_round *t)
{
    t->value -= 1;
    update_round_timer(base, t);
}

/* apple functions */
apple *generate_apple(UINT16 col)
{
    static apple A;
        A.y = 0;
        A.x = (col * 32) + 128; /* lines the apple up into one of 12 columns */
        A.height = APPLE_HEIGHT;
        A.width = APPLE_WIDTH;
    return &A;
}

void move_apple(UINT32 *base, apple *this_apple)
{
    clear_apple(base, this_apple->x, this_apple->y, APPLE_WIDTH, APPLE_HEIGHT);
    this_apple->y += 2;
    plot_apple_32(base, this_apple->x, this_apple->y, apple_bitmap, APPLE_HEIGHT);
}
