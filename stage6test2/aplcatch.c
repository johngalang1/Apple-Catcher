#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include "renderer.h"
#include "input.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: aplcatch.c
PURPOSE: CONTAINS MAIN GAME LOOP WITH MULTIPLE APPLES
*/ 

UINT8 back_buffer_array[32260]; 

/* Function to allocate and align back buffer */
UINT32* allocate_back_buffer();

/* Function to flip buffers: display back_buffer and swap with front_buffer */
UINT32* flip_buffers(UINT32 **front_buffer, UINT32 **back_buffer);

/* Function to get the current clock time from the vertical blank counter */
unsigned long get_time();
void run_start_timer(model *curr_model, UINT32 *back_buffer, 
                    unsigned long timeThen, unsigned long timeNow);

int main() {
    int quit = 0;
    int app_count, app_collision;
    unsigned long timeThen, timeNow;
    int tickCounter = 0;  /* Counter to track ticks for 1-second intervals */
    char input;  
    UINT32 *front_buffer = (UINT32 *)Physbase();       /* Screen’s original buffer */
    UINT32 *back_buffer = allocate_back_buffer();      /* Aligned back buffer */ 
    UINT32 *original_buffer = (UINT32 *)Physbase();  /* Store the original buffer */
    UINT32 *curr_buffer = back_buffer;              /* Start with Back buffer*/    

    /* Initialize model and set up timing */
    model *curr_model = init_model();
    timeThen = get_time();  

    Setscreen(-1, curr_buffer, -1); 

    input_init();

    clear_screen(front_buffer); 
    clear_screen(back_buffer);  

    render_borders((UINT16 *)front_buffer);
    render_borders((UINT16 *)back_buffer);

    render_start_timer((UINT16 *)back_buffer, &(curr_model->st));
    render_round_timer((UINT16 *)back_buffer, &(curr_model->rt));
    render_score((UINT16 *)back_buffer, &(curr_model->curr_score));
    render_score((UINT16 *)front_buffer, &(curr_model->curr_score));
    
    run_start_timer(curr_model, back_buffer, timeThen, timeNow);

    update_model(curr_buffer, (UINT16*) curr_buffer, &(curr_model->apples[0]), 
                 &(curr_model->b), &(curr_model->curr_score), 
                 &(curr_model->rt)); 

    /* Main game loop */
    while (!quit && curr_model->rt.value > 0) {
        if (check_input()) {
            input = get_input();

            if (input == 'q' || input == 'Q') {
                quit = 1;
            } else {
                process_input(input, &quit);
                render_basket(back_buffer, &(curr_model->b), -1);  
                render_basket(front_buffer, &(curr_model->b), -1);  
                move_basket_based_on_input(&(curr_model->b));
            }
        } 

        /* Update and render on each clock tick */
        timeNow = get_time();
        if (timeNow != timeThen) {
            int b_collision = check_basket_collision(&(curr_model->b), 0);
            tickCounter++;

            /* Every 70 ticks, decrement the round timer by 1 second */
            if (tickCounter >= 70) {
                decrement_round_timer(&(curr_model->rt));
                tickCounter = 0;
            }
            render_basket(curr_buffer, &(curr_model->b), 1);    

            /* move and check all apples */
            for (app_count = 0; app_count < 3; app_count++)
            {
                render_apple((UINT32 *)back_buffer, &(curr_model->apples[app_count]), -1); /* remove apples old posiition from back buffer */

                app_collision = move_apple(curr_model, app_count); /* check for collision */
                switch(app_collision){
                    case 0: /* no collision */
                        break;
                    case 1: /* apple_basket_collision */
                        increment_score(curr_model);
                        render_score((UINT16 *)back_buffer, &(curr_model->curr_score)); 
                        render_score((UINT16 *)front_buffer, &(curr_model->curr_score));
                        render_apple((UINT32 *)front_buffer, &(curr_model->apples[app_count]), -1);  
                        reset_apple_position(&(curr_model->apples[app_count]));
                        break;
                    case 2: /* apple_ground_collision*/
                        render_apple((UINT32 *)front_buffer, &(curr_model->apples[app_count]), -1);  
                        reset_apple_position(&(curr_model->apples[app_count]));
                        break;                        
                }
                render_apple((UINT32 *)back_buffer, &(curr_model->apples[app_count]), 1);  /* plot apples new position */
            }

            render_round_timer((UINT16*)curr_buffer, &(curr_model->rt));
            Vsync();
            Setscreen(-1, curr_buffer, -1);
            curr_buffer = flip_buffers(&front_buffer, &back_buffer);  

            /* Update timeThen to track the next tick */
            timeThen = timeNow;
        }
    }
    render_message((UINT16*) curr_buffer); 
    Setscreen(-1, original_buffer, -1);
    return 0;
} 

void run_start_timer(model *curr_model, UINT32 *back_buffer, 
                    unsigned long timeThen, unsigned long timeNow) 
{
    int tickCounter = 0;

    timeThen = get_time();

    while (curr_model->st.value >= -1) {
        timeNow = get_time();
        if (timeNow != timeThen) {
            tickCounter++;
        }
        if (tickCounter >= 70) {
            if (curr_model->st.value > 0) {
                render_start_timer((UINT16 *)back_buffer, &(curr_model->st));
            } else {
                plot_char((UINT16 *)back_buffer, curr_model->st.x, curr_model->st.y, 
                          letterG_bitmap, curr_model->st.height);
                plot_char((UINT16 *)back_buffer, curr_model->st.x + 16, curr_model->st.y,
                          letterO_bitmap, curr_model->st.height);
            }
            decrement_start_timer(&(curr_model->st));
            tickCounter = 0;
        }
        timeThen = timeNow;
    }

    clear_char((UINT16 *)back_buffer, curr_model->st.x, curr_model->st.y, curr_model->st.height);
    clear_char((UINT16 *)back_buffer, curr_model->st.x + 16, curr_model->st.y, curr_model->st.height);
} 

unsigned long get_time() {
    unsigned long *timer_address = (unsigned long *)0x462;
    unsigned long time;

    unsigned long old_sr = Super(0);  
    time = *timer_address;
    Super(old_sr);                    

    return time;
}  

UINT32* flip_buffers(UINT32 **front_buffer, UINT32 **back_buffer) {
    /* Swap front and back buffers */
    UINT32 *temp = *front_buffer;
    *front_buffer = *back_buffer;
    *back_buffer = temp;
    return *front_buffer;
} 

UINT32* allocate_back_buffer() {
    UINT8 *temp = back_buffer_array;

    /* Align to the nearest 256-byte boundary using bitwise operations */
    temp = (UINT8*)(((UINT32)temp + 255) & ~255);
    
    return (UINT32*)temp;
}