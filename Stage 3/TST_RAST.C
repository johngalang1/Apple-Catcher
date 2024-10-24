#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"

int main()
{
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    apple falling_apple = {200, -32, 32, 32};  /* Apple starting above the screen */
    basket player_basket = {200, SCREEN_HEIGHT - 32, 8, 64, 16, basket_bitmap};  /* Basket near the bottom */ 

    score *new_score = init_score();
    timer_round *round_timer = init_round_timer();
    
    /* Define a message struct */
    message game_message;
    game_message.start_x = (SCREEN_WIDTH - (12 * 16)) / 2;  /* Center the message horizontally */
    game_message.start_y = 20;   /* Vertical position at the top of the screen */
    game_message.spacing = 16;   /* Spacing between letters */
    game_message.text = "TIME UP"; /* The message text */
    
    /* Seed the random number generator */
    srand(time(NULL));
    clear_screen(FB32);  /* Clear the screen */
    /* Plot vertical lines 128 pixels from the left and right borders */
    plot_vertical_line(FB16, LEFT_BORDER, 0, SCREEN_HEIGHT);  /* Left border */
    plot_vertical_line(FB16, SCREEN_WIDTH - 128, 0, SCREEN_HEIGHT);  /* Right border */ 

    update_score(FB16, new_score);
    update_round_timer(FB16, round_timer);

    while (new_score->value < 10)  /* Game loop with timer */
    {
        /* Clear the previous position of the apple and basket */
        clear_apple(FB32, falling_apple.x, falling_apple.y, falling_apple.width, falling_apple.height);
        clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);

        /* Move the apple down */
        falling_apple.y += 4;  /* Move apple down by 4 pixels each frame */

        /* Check if the apple reaches the bottom of the screen */
        if (falling_apple.y > SCREEN_HEIGHT) {
            /* Call the function to randomize the apple's position */
            reset_apple_position(&falling_apple);
        }

        /* Check if the apple collides with the basket using the collision function */
        if (check_apple_collision(&player_basket, &falling_apple)) {
            /* Increment score outside of the collision check */
            increment_score(FB16, new_score);
            reset_apple_position(&falling_apple);  /* Reset the apple */
        }

        /* Plot the basket at the new position */
        plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);

        /* Plot the apple at the new position */
        plot_apple_32(FB32, falling_apple.x, falling_apple.y, apple_bitmap, falling_apple.height);

        /* Delay for visualization (e.g., 1/70th of a second) */
        Vsync();
    }

    display_message(&game_message);

    return 0;
}
