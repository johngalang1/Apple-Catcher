#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include "renderer.h"
#include "input.h"  
#include "music.h"
#include "effects.h"
#include "splash.h" 

/* 
AUTHORS: John G, Zach L
FILE NAME: aplcatch.c
PURPOSE: CONTAINS MAIN GAME 
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

int handle_splash_screen(UINT32 *original_buffer);

void play_game(UINT32 *original_buffer);

int main() {
    /* Initialize the original buffer for splash screen */
    UINT32 *original_buffer = (UINT32 *)get_video_base();

    while (1) {
        /* Call function to handle the splash screen and menu */
        int option = handle_splash_screen(original_buffer);

        if (option == 0) {
            /* Quit selected */
            break;
        } else if (option == 1) {
            /* Start 1-player game */
            play_game(original_buffer);
        } else if (option == 2) {
            /* Placeholder for future 2-player game functionality */
        }
    }
    return 0;
}


int handle_splash_screen(UINT32 *original_buffer) {
    int selected_option = 0; /* Default to "Player - 1" */
    char input;
    /* Clear the screen and plot the splash screen */
    clear_screen(original_buffer);
    plot_splash_screen(original_buffer, splash_screen, 640, 400);

    /* Display splash screen continuously until valid input */
    while (1) {
        /* Wait for user input */
        if (check_input()) {
            input = get_input();
            switch (input) {
                case '1':
                    return 1; /* Player 1 selected */
                case '2':
                    return 2; /* Player 2 selected (Future functionality) */
                case 'q': case 'Q':
                    return 0; /* Quit selected */
                default:
                    break; /* Ignore invalid input */
            }
        }
    }
}

void play_game(UINT32 *original_buffer) {
    int quit = 0;
    int app_count, app_collision;
    int input_flag = 0;
    unsigned long timeThen, timeNow;
    int tickCounter = 0;  /* Counter to track ticks for 1-second intervals */
    int sound_effect_timer = 0; /* Timer for sound effect duration */
    char input;   
    unsigned long music_time_counter = 0; /* Counter for music updates */ 
    int delay_counter; 
    unsigned long end_start_time, end_current_time;

    /* Initialize buffers for the game loop */
    UINT32 *front_buffer = (UINT32 *)get_video_base();
    UINT32 *back_buffer = allocate_back_buffer();
    UINT32 *curr_buffer = back_buffer;

    /* Initialize model and set up timing */
    model *curr_model = init_model();
    timeThen = get_time();  

    clear_screen(original_buffer); 
    set_video_base(curr_buffer);  
    Vsync();

    input_init();

    render_pregame(front_buffer, back_buffer, curr_model);

    run_start_timer(curr_model, back_buffer, timeThen, timeNow);

    /* Play Music */ 
    start_music();
    update_model(curr_buffer, (UINT16*) curr_buffer, &(curr_model->apples[0]), 
                 &(curr_model->b), &(curr_model->curr_score), 
                 &(curr_model->rt)); 

    /* Main game loop */
    while (!quit) {  
        input_flag = 0;
        if (check_input()) {
            input = get_input();
            if (input == 'q' || input == 'Q') {
                quit = 1;
            } else { 
                input_flag = 1;
                process_input(input, &quit);
            }
        } 

        /* Update and render on each clock tick */
        timeNow = get_time();
        if (timeNow != timeThen) {
            int b_collision = check_basket_collision(&(curr_model->b), 0);
            tickCounter++;  

        if (input_flag == 1)
        { 
            render_basket(back_buffer, &(curr_model->b), -1);  
            render_basket(front_buffer, &(curr_model->b), -1);  
            move_basket_based_on_input(&(curr_model->b));
        }

            /* Update music every tick */
            update_music(&music_time_counter);

            /* Handle sound effect timing */
            if (sound_effect_timer > 0) {
                sound_effect_timer--;
                if (sound_effect_timer == 0) {
                        enable_channel(2, 0, 0);     
                }
            }

            /* Every 70 ticks, decrement the round timer by 1 second */
            if (tickCounter >= 70) {
                decrement_round_timer(&(curr_model->rt));
                tickCounter = 0;
                if(curr_model->rt.value <= 0){
                    quit = 1;
                }
            }
            render_basket(curr_buffer, &(curr_model->b), 1);    

            /* move and check all apples */
            for (app_count = 0; app_count < 3; app_count++) {
                render_apple((UINT32 *)back_buffer, &(curr_model->apples[app_count]), -1); /* remove apples old position from back buffer */

                app_collision = move_apple(curr_model, app_count); /* check for collision */
                switch(app_collision) {
                    case 0: /* no collision */
                        break;
                    case 1: /* apple_basket_collision */ 
                        play_score();  /* Trigger score sound */
                        sound_effect_timer = 10; /* Set sound duration (~0.14s) */
                        increment_score(curr_model);
                        render_score((UINT16 *)back_buffer, &(curr_model->curr_score)); 
                        render_score((UINT16 *)front_buffer, &(curr_model->curr_score));
                        render_apple((UINT32 *)front_buffer, &(curr_model->apples[app_count]), -1);  
                        reset_apple_position(&(curr_model->apples[app_count]));
                        break;
                    case 2: /* apple_ground_collision */
                        play_splat();  /* Trigger splat sound */
                        sound_effect_timer = 10; /* Set sound duration (~0.14s) */
                        render_apple((UINT32 *)front_buffer, &(curr_model->apples[app_count]), -1);  
                        reset_apple_position(&(curr_model->apples[app_count]));
                        break;                        
                }
                render_apple((UINT32 *)back_buffer, &(curr_model->apples[app_count]), 1);  /* plot apples new position */
            }

            render_round_timer((UINT16*)curr_buffer, &(curr_model->rt));
            Vsync();
            set_video_base(curr_buffer); 
            curr_buffer = flip_buffers(&front_buffer, &back_buffer);  

            /* Update timeThen to track the next tick */
            timeThen = timeNow;
        }
    } 
    stop_sound();
    delay_counter = 0;
    end_start_time = get_time();
    while (delay_counter < 350) { /* 70 ticks/second * 5 seconds = 350 ticks */ 
    end_current_time = get_time();
    if (end_current_time != end_start_time) { 
        delay_counter++;
        end_start_time = end_current_time; 

        render_message((UINT16*) back_buffer);   
        Vsync();
        }
    }
    clear_screen(front_buffer); 
    clear_screen(back_buffer);  
    set_video_base(original_buffer);   
    Vsync();
}  

UINT32* allocate_back_buffer() {
    UINT8 *temp = back_buffer_array;

    /* Align to the nearest 256-byte boundary using bitwise operations */
    temp = (UINT8*)(((UINT32)temp + 255) & ~255);
    
    return (UINT32*)temp;
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
