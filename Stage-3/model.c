#include "model.h"

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

basket *init_basket()
{
    static basket player_basket;
        player_basket.x = 128;
        player_basket.y = 364;
        player_basket.delta_x = 8;
        player_basket.width = BASKET_WIDTH;
        player_basket.height = BASKET_HEIGHT;
        player_basket.bitmap = basket_bitmap;
    return &player_basket;
}

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

apple apples[NUM_APPLES];

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
void generate_apple(UINT16 col)
{
    static int apple_count = 0;
    apple *A = &apples[apple_count];
    
        A->y = -32;              /* apples start off-screen */
        A->x = (col * 32) + 128; /* lines the apple into one of 12 columns */
        A->height = APPLE_HEIGHT;
        A->width = APPLE_WIDTH;
    
    apple_count++;
}

/*
NAME: move_apple
PARAMETERS: *base - framebuffer, *this_apple - pointer to the apple structure
PURPOSE: To move an apple downward on the screen by a fixed increment.
DETAILS: Clears the apple's previous position, increments its y-coordinate, and plots it in the new position.
*/
void move_apple(UINT32 *base, apple *this_apple)
{
    clear_apple(base, this_apple->x, this_apple->y, APPLE_WIDTH, APPLE_HEIGHT);
    this_apple->y += 2;
    plot_apple_32(base, this_apple->x, this_apple->y, apple_bitmap, APPLE_HEIGHT);
} 
