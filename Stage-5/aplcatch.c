#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include "renderer.h"
#include "driver.h" 
#include "input.h"
#include "time.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: aplcatch.c
PURPOSE: CONTAINS MAIN GAME LOOP
*/

int main() {
    int quit = 0;
    unsigned long timeThen, timeNow;
    int tickCounter = 0;  /* Counter to track ticks for 1-second intervals */
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    char input;

    model *curr_model = init_model();
    timeThen = get_time();  
    clear_screen(FB32); 
    input_init();
    render_model(FB32, FB16, &(curr_model->apples[0]), &(curr_model->b),
                        &(curr_model->curr_score), &(curr_model->rt), &(curr_model->st)); 

    /* Main game loop */
    while (!quit && curr_model->rt.value > 0) {
        if (check_input()) {
            input = get_input();

            if (input == 'q' || input == 'Q') {
                quit = 1;
            } else {
                process_input(input, &quit);
            }
        }

        timeNow = get_time();
        if (timeNow != timeThen) {
            int b_collision = check_basket_collision(&(curr_model->b), 0);
            int a_collision = check_apple_collision(&(curr_model->b), &(curr_model->apples[0]));
            tickCounter++;

            /* Every 70 ticks, decrement the round timer by 1 second */
            if (tickCounter >= 70) {
                decrement_round_timer(FB16, &(curr_model->rt));
                tickCounter = 0;  /* Reset tick counter for the next second */
            }
            /* Erase and update basket based on user input */
            render_basket(FB32, &(curr_model->b), -1);
            move_basket_based_on_input(&(curr_model->b));
            render_basket(FB32, &(curr_model->b), 1);

            /* Update and move apple */
            render_apple(FB32, &(curr_model->apples[0]), -1);
            move_apple(&(curr_model->apples[0]));
            if (a_collision > 0) {
                increment_score(&(curr_model->curr_score));
                render_score(FB16, &(curr_model->curr_score));
                reset_apple_position(&(curr_model->apples[0]));
            }

            /* Reset apple if it reaches the bottom */
            if (curr_model->apples[0].y == 368) {
                reset_apple_position(&(curr_model->apples[0]));
            }
            render_apple(FB32, &(curr_model->apples[0]), 1);

            /* Update timeThen to track the next tick */
            timeThen = timeNow;
        }
    }

    return 0;
}
