#include "model.h"
#include "renderer.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: model.c
PURPOSE: CONTAINS FUNCTIONS FOR OBJECT BEHAVIOURS
*/

/*
NAME: move_basket
PARAMETERS: *b - pointer to the basket structure, 
            direction - integer indicating movement direction
PURPOSE: To update the basket's horizontal position based on the specified direction.
DETAILS: Adjusts the basket’s x-position and ensures it stays within screen boundaries.
*/
model *init_model()
{
    int i;
    static model curr_model;
    for(i = 0; i < 3; i++)
    {
        curr_model.apples[i] = generate_apple(i);
    }
        curr_model.b = init_basket();
        curr_model.curr_score = init_score();
        curr_model.rt = init_round_timer();
        curr_model.st = init_start_timer();
    return &curr_model;
}

void move_basket(basket *b, int direction)
{
    /* Update the basket's horizontal position based on direction */
    b->x += direction * b->delta_x;
}

basket init_basket()
{
    static basket player_basket;
        player_basket.x = 448;
        player_basket.y = 364;
        player_basket.delta_x = 2;
        player_basket.width = BASKET_WIDTH;
        player_basket.height = BASKET_HEIGHT;
        player_basket.bitmap = basket_bitmap;
    return player_basket;
}

/* only a testing function to allow the setting of basket x values */
void set_basket(basket *b, UINT16 set_x)
{
    b->x = set_x;
}

/* score functions */

score init_score()
{
    static score game_score;
        game_score.digit1_x = 32; /* ones digit */
        game_score.digit1_y = 16;
        game_score.digit2_x = 16; /* tens digit */
        game_score.digit2_y = 16;
        game_score.height = CHARACTER_HEIGHT;
        game_score.value = 0;
    return game_score;
}

/* a testing function to reset score */
void reset_score(score *score)
{
    score->value = 0;
}

/* a testing function to set score to a specific value */
void set_score(score *score, int x)
{
    score->value = x;
}

/* round timer functions */

timer_round init_round_timer()
{
    static timer_round t;
        t.digit1_x = 608; /* ones digit */
        t.digit1_y = 16;
        t.digit2_x = 592; /* tens digit */
        t.digit2_y = 16;
        t.height = CHARACTER_HEIGHT;
        t.value = 60; 
    return t;
}

void set_round_timer(timer_round *t, int x)
{
    t->value = x;
}

/* start timer functions */
timer_start init_start_timer()
{
    static timer_start t;
        t.x = 288;
        t.y = 200;
        t.height = CHARACTER_HEIGHT;
        t.value = 5;
    return t;
}

void set_start_timer(timer_start *st, int x)
{
    st->value = x;
}

/* apple functions */
/* 
NAME: generate_apple
PARAMETERS: UINT16 col
PURPOSE: to initialize an apple object to a specific column (x value) 
        and assign it to an index in the apple array.
DETAILS: keeps track of how many apples have been created and uses
        that tracker to assign each new apple to a unique index in 
        the apple array (no need for return). Each apple's inital y
        value is -32 which means it will not be on-screen immediately, 
        this is so that apples will "fall" onto the screen instead of 
        just appearing at y = 0. (col * 32) + 128 assigns the x value 
        to plot the apple into one of 12 columns in the play area (0 - 11). 
EXAMPLE CALL: generate_apple(n) where n represents an integer 0 - 11 for 
            desired column.
*/
apple generate_apple(UINT16 col)
{
    apple A;
    
        A.y = -32;              /* apples start off-screen */
        A.x = (col * 32) + 128; /* lines the apple into one of 12 columns */
        A.height = APPLE_HEIGHT;
        A.width = APPLE_WIDTH;
    return A;
}

void move_apple(apple *this_apple)
{
    this_apple->y += 2;
} 

/* a testing function to reset the y value of an apple */
void set_apple(apple *a, int x, int y)
{
    a->y = y;
    a->x = x;
}
