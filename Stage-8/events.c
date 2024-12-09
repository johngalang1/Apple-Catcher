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


void increment_score(model *curr_model)
{ 
    curr_model->curr_score.value += 1;
}


void decrement_round_timer(timer_round *t) {
    /* Check if the timer is greater than zero before decrementing */
    if (t->value > 0) {
        t->value--;  /* Decrement timer value by 1 second */ 
    }
}

void decrement_start_timer(timer_start *t)
{
    t->value--;
}


/*
NAME: check_apple_collision
PARAMETERS: *curr_model - a pointer to the model containing the list of apples
            i - used to get the index of the apple currently moving
PURPOSE: To detect if a collision has occurred between the apple and the basket.
DETAILS: Checks for overlap between the apple and basket on both the x and y axes, 
        returns 1 if a collision is detected and 0 otherwise.
*/
int apple_basket_collision(model *curr_model, int i)
{
    /* check height first because it will (theoretically) be true less often */
    /* slightly lower clock cycles used for checking */
    if (curr_model->apples[i].y + APPLE_HEIGHT >= curr_model->b.y)  /* apple is at y-axis to check */
    {
        if ((curr_model->apples[i].x + curr_model->apples[i].width > curr_model->b.x)
         && (curr_model->apples[i].x < curr_model->b.x + curr_model->b.width))  /* X-axis overlap */
        {
            return 1;  
        }
    }
    return 0; 
}

int apple_floor_collision(model *curr_model, int i)
{
    return curr_model->apples[i].y == 368;
}

/*
NAME: reset_apple_position
PARAMETERS: *a - pointer to the apple structure
PURPOSE: To set a random x-position for the apple and reset its y-position above the screen.
DETAILS: Randomizes the apple's x-position within screen borders and sets its y-position to start above the visible area.
*/
void reset_apple_position(apple *a)
{   
    a->x =  LEFT_BORDER + 1 + ((rand() % 11) * 32);
    
    /* Reset y-position to just above the screen */
    a->y = -a->height;
}