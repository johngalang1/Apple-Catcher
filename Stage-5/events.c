#include <stddef.h>  
#include <osbind.h>  
#include "events.h"
#include "raster.h"
/* 
AUTHORS: John G, Zach L
FILE NAME: events.c
PURPOSE: CONTAINS ALL FUNCTIONS FOR ASYCHRONOUS AND SYNCHRONOUS EVENTS
*/

/*
NAME: check_basket_collision
PARAMETERS: *b - pointer to a basket structure
PURPOSE: To prevent the basket from moving beyond the left or right screen borders.
DETAILS: Checks the basket’s position against the left and right borders and adjusts it to stay within bounds.
*/
int check_basket_collision(basket *b, int direction)
{
    if (b->x <= LEFT_BORDER + 32)  
    {
        b->x = LEFT_BORDER + 32;  
        return 1;  /* Collision on the left side */
    }
    else if (b->x >= RIGHT_BORDER - b->width) 
    {
        b->x = RIGHT_BORDER - b->width; 
        return 1;  /* Collision on the right side */
    }
    return 0;  /* No collision */
}


void increment_score(score *curr_score)
{ 
    curr_score->value += 1;
}


void decrement_round_timer(timer_round *t)
{
    t->value -= 1;
}


/*
NAME: check_apple_collision
PARAMETERS: *b - pointer to the basket structure, 
            *a - pointer to the apple structure
PURPOSE: To detect if a collision has occurred between the apple and the basket.
DETAILS: Checks for overlap between the apple and basket on both the x and y axes, 
        returns 1 if a collision is detected and 0 otherwise.
*/
int check_apple_collision(basket *b, apple *a)
{
    /* Check if the apple is within the horizontal bounds of the basket */
    if ((a->x + a->width > b->x) && (a->x < b->x + b->width))  /* X-axis overlap */
    {
        /* Check if the apple has reached the basket's vertical position */
        if (a->y + a->height >= b->y)  /* Y-axis overlap */
        {
            return 1;  
        }
    }
    return 0; 
}

/*
NAME: reset_apple_position
PARAMETERS: *a - pointer to the apple structure
PURPOSE: To set a random x-position for the apple and reset its y-position above the screen.
DETAILS: Randomizes the apple's x-position within screen borders and sets its y-position to start above the visible area.
*/
void reset_apple_position(apple *a)
{
    /* Randomize x-position within the defined borders */
    a->x = (LEFT_BORDER + 1) + (rand() % (RIGHT_BORDER - LEFT_BORDER - a->width));
    
    /* Reset y-position to just above the screen */
    a->y = -a->height;
}


