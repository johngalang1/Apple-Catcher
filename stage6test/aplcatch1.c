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

#define BUFFER_SIZE 32256  /* Size of the back buffer with extra space for alignment */
const UINT8 buffer[BUFFER_SIZE];  /* Declare the back buffer globally */
unsigned long get_time();

UINT32* allocate_back_buffer() {
    UINT32 *buffer_aligned = (UINT32 *)(((UINT32)buffer + 255) & ~255);  /* Align to 256 bytes */
    return buffer_aligned;
}

void clear_buffer(UINT32 *buffer) {
    clear_screen(buffer);  /* Clear function that fills the buffer with a blank frame */
}

void render_frame_to_buffer(UINT32 *buffer, model *curr_model) {
    render_basket(buffer, &(curr_model->b), -1);
    move_basket_based_on_input(&(curr_model->b));
    render_basket(buffer, &(curr_model->b), 1);

    render_apple(buffer, &(curr_model->apples[0]), -1);
    move_apple(&(curr_model->apples[0]));
    if (check_apple_collision(&(curr_model->b), &(curr_model->apples[0])) > 0) {
        increment_score(&(curr_model->curr_score));
        render_score((UINT16 *)buffer, &(curr_model->curr_score));
        reset_apple_position(&(curr_model->apples[0]));
    }
    if (curr_model->apples[0].y == 368) {
        reset_apple_position(&(curr_model->apples[0]));
    }
    render_apple(buffer, &(curr_model->apples[0]), 1);
}

void swap_buffers(UINT32 **front_buffer, UINT32 **back_buffer) {
    UINT32 *temp = *back_buffer;
    *back_buffer = *front_buffer;  /* Swap pointers */
    *front_buffer = temp;
}

int main() {
    int quit = 0;
    unsigned long timeThen, timeNow;
    int tickCounter = 0;
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    char input;

    UINT32 *front_buffer = (UINT32*)FB32;         /* Use the screen buffer as the initial front buffer */
    UINT32 *back_buffer = allocate_back_buffer();  /* Allocate and align the back buffer */

    model *curr_model = init_model();
    timeThen = get_time();
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
        
        Vsync();
        timeNow = get_time();
        if (timeNow != timeThen) {
            tickCounter++;
            if (tickCounter >= 70) {
                decrement_round_timer((UINT16 *)back_buffer, &(curr_model->rt));
                tickCounter = 0;
            }

            render_frame_to_buffer(back_buffer, curr_model);
            Setscreen(*back_buffer, -1, -1); 
            swap_buffers(&front_buffer, &back_buffer);

            timeThen = timeNow;
        }
    }

    Setscreen(FB32, -1, -1);  /* Restore the original front buffer on exit */
    return 0;
}

/* Function to get the current clock time from the vertical blank counter */
unsigned long get_time() {
    unsigned long *timer_address = (unsigned long *)0x462;
    unsigned long time;

    /* Switch to supervisor mode and read timer */
    unsigned long old_sr = Super(0);  
    time = *timer_address;
    Super(old_sr);                    

    return time;
}
