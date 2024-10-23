#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"

int main()
{
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = Physbase();
    score *new_score = init_score();
    timer_round *round_timer = init_round_timer();
    int direction = 1;  /* Start by moving to the right */
    basket player_basket = {300, 150, 8, 64, 16, basket_bitmap};  /* Initial basket position */
    
    clear_screen(FB32);
    
    /* Plot vertical lines 128 pixels from the left and right borders */
    plot_vertical_line(FB16, LEFT_BORDER, 0, SCREEN_HEIGHT);  /* Left border */
    plot_vertical_line(FB16, RIGHT_BORDER, 0, SCREEN_HEIGHT);  /* Right border */
    
    update_score(FB16, new_score);
    update_round_timer(FB16, round_timer);
    
    Cnecin();
    
    while (round_timer->value > 0)
    {
        /* Clear the previous position of the basket */
        clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);

        /* Move the basket */
        move_basket(&player_basket, direction);

        /* Plot the basket at the new position */
        plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);

        /* Check for boundaries and change direction if necessary */
        if (player_basket.x <= LEFT_BORDER + 32)  /* Adjust for basket width */
        {
            direction = 1;  /* Start moving right */
            increment_score(FB16, new_score);
            decrement_round_timer(FB16, round_timer);
        }
        else if (player_basket.x >= RIGHT_BORDER - player_basket.width)  /* Hit right border */
        {
            player_basket.x = RIGHT_BORDER - player_basket.width;  /* Prevent overlap */
            direction = -1;  /* Start moving left */
            increment_score(FB16, new_score);
            decrement_round_timer(FB16, round_timer);
        }

        /* Delay for visualization (e.g., 1/70th of a second) */
        Vsync();  
    }

    return 0;
}
