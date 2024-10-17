#include "model.h"

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
