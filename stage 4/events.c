#include <stddef.h>  
#include <osbind.h>  
#include "events.h"
#include "raster.h"

/* Function to check basket collision with borders */
int check_basket_collision(basket *b, int direction)
{
    if (b->x <= LEFT_BORDER + 32)  /* Adjust for basket width */
    {
        b->x = LEFT_BORDER + 32;  /* Prevent going beyond the left border */
        direction = 0;
    }
    else if (b->x >= RIGHT_BORDER - b->width) /* Hit right border */
    {
        b->x = RIGHT_BORDER - b->width;  /* Prevent overlap */
        direction = 0;
    }
    return direction;
}


void increment_score(score *curr_score)
{ 
    curr_score->value += 1;
}


void decrement_round_timer(UINT16 *base, timer_round *t)
{
    t->value -= 1;
    render_round_timer(base, t);
}



int check_apple_collision(basket *b, apple *a)
{
    /* Check if the apple is within the horizontal bounds of the basket */
    if ((a->x + a->width > b->x) && (a->x < b->x + b->width))  /* X-axis overlap */
    {
        /* Check if the apple has reached the basket's vertical position */
        if (a->y + a->height >= b->y)  /* Y-axis overlap */
        {
            return 1;  /* Collision occurred */
        }
    }
    return 0;  /* No collision */
}


/* Function to generate a random x-position for the apple */
void reset_apple_position(apple *a)
{
    /* Randomize x-position within the defined borders */
    a->x = (LEFT_BORDER + 1) + (rand() % (RIGHT_BORDER - LEFT_BORDER - a->width));
    
    /* Reset y-position to just above the screen */
    a->y = -a->height;
}


