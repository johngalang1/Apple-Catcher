#include "driver.h"
#include <osbind.h>

/* 
AUTHORS: John G, Zach L
FILE NAME: driver.c
PURPOSE: CONTAINS FUNCTIONS FOR TESTING RENDERING
*/

/*
NAME: test_basket_render
PARAMETERS: *base32 - framebuffer (32-bit), 
            *base16 - framebuffer (16-bit), 
            *b - pointer to the basket structure
PURPOSE: To render and move the basket back and forth across the screen, detecting collisions with screen borders.
DETAILS: Clears the screen, renders borders, sets an initial position for the basket, 
        and alternates movement direction upon collision, repeating until three collisions occur.
*/
void test_basket_render(UINT32 *base32, UINT16 *base16, basket *b)
{
    int direction = -1;
    int total_collisions = 0;
    int collision_detected;
    clear_screen(base32);
    render_borders(base16);
    set_basket(b, 448);
    render_basket(base32, b, 1);
    
    /* loop to test the rendering */
    while(total_collisions < 3)
    {
        render_basket(base32, b, -1);   
        move_basket(b, direction);
        collision_detected = check_basket_collision(b, direction);
        if(collision_detected == 0)
        {
            total_collisions++;
            direction = -direction;
        }
        render_basket(base32, b, 1);

        Vsync();
    }

}

/*
NAME: test_apple_render
PARAMETERS: *base32 - framebuffer (32-bit), 
            *base16 - framebuffer (16-bit), 
            *a - pointer to the apple structure, 
            *b - pointer to the basket structure
PURPOSE: To render and drop multiple apples from the top of the screen to simulate falling apples.
DETAILS: Clears the screen, sets initial positions for the apple and basket, and moves the apple down. 
        Resets the apple's position when it reaches the bottom, repeating until four drops occur.
*/
void test_apple_render(UINT32 *base32, UINT16 *base16, apple *a, basket *b)
{
    int total_drops = 0;
    int reset = 0;
    clear_screen(base32);
    
    set_basket(b, 0); /* only testing apple falling to bottom so remove basket from the play area */
    render_borders(base16);
    set_apple(a, 224, -32);
    render_apple(base32, a, 1);

    while(total_drops < 4)
    {
        render_apple(base32, a, -1);
        move_apple(a);
        reset = check_apple_collision(b, a);
        if(a->y == 368)
        {
            reset_apple_position(a);
            total_drops++;
        }

        render_apple(base32, a, 1);
        Vsync();
    }
}

/*
NAME: test_score_render
PARAMETERS: *base32 - framebuffer (32-bit), 
            *base16 - framebuffer (16-bit), 
            *a - pointer to the apple structure, 
            *b - pointer to the basket structure, 
            *score - pointer to the score structure
PURPOSE: To render the score and update it based on collisions between the apple and basket.
DETAILS: Sets initial positions for the apple, basket, and score, and moves the apple downward. 
        Increments the score upon each collision with the basket, resetting the apple's position 
        after each drop, until a score of 4 is reached.
*/
void test_score_render(UINT32 *base32, UINT16 *base16, apple *a, basket *b,
                        score *score)
{
    int collision = 0;
    clear_screen(base32);
    set_basket(b, 192);
    set_apple(a, 192, -32);
    reset_score(score);

    render_borders(base16);
    render_apple(base32, a, 1);
    render_basket(base32, b, 1);
    render_score(base16, score);

    while(score->value < 4)
    {
        render_apple(base32, a, -1);
        move_apple(a);
        collision = check_apple_collision(b, a);
        if(collision > 0)
        {
            increment_score(score);
            render_score(base16, score);
            reset_apple_position(a);
        }
        if(a->y == 368)
        {
            reset_apple_position(a);
        }
        render_apple(base32, a, 1);
        Vsync();
    }
}
/*
NAME: test_frame_render
PARAMETERS: *base32 - framebuffer (32-bit), 
            *base16 - framebuffer (16-bit), 
            *a - pointer to the apple structure, 
            *b - pointer to the basket structure, 
            *score - pointer to the score structure, 
            *rt - pointer to the round timer structure
PURPOSE: To render a complete frame displaying apples, basket, score, timer, and borders.
DETAILS: Sets initial positions and values for the basket, apples, score, and timer, 
        and renders each element along with screen borders in a single frame.
*/
void test_frame_render(UINT32 *base32, UINT16 *base16, apple *a, basket *b,
                        score *score, timer_round *rt)
{
    clear_screen(base32);
    set_basket(b, 200);
    set_apple(a, 200, 240);
    set_apple(&apples[1], 320, 0); /* extra apple for the test */
    set_round_timer(rt, 27);
    set_score(score, 31);

    render_borders(base16);
    render_apple(base32, a, 1);
    render_apple(base32, &apples[1], 1);
    render_basket(base32, b, 1);
    render_round_timer(base16, rt);
    render_score(base16, score);
    Cnecin();
}
/*
NAME: test_master_render
PARAMETERS: *base32 - framebuffer (32-bit), 
            *base16 - framebuffer (16-bit), 
            *a - pointer to the apple structure, 
            *b - pointer to the basket structure, 
            *score - pointer to the score structure, 
            *rt - pointer to the round timer structure, 
            *st - pointer to the start timer structure
PURPOSE: To render and simulate a complete game sequence, updating the basket, apple, score, round timer, and start timer.
DETAILS: Moves the basket and apple, checks for collisions to update the score, resets apple position as needed, 
        and decrements the round timer based on a simulated clock, continuing until a score of 11 or timer expiration.
*/
void test_master_render(UINT32 *base32, UINT16 *base16, apple *a, basket *b,
                        score *score, timer_round *rt, timer_start *st)
{
    int fake_clock = 0;
    int direction = -1;
    int b_collision;
    int a_collision;
    clear_screen(base32);
    set_basket(b, 448);
    set_apple(a, 384, -32);
    reset_score(score);
    set_round_timer(rt, 60);
    set_start_timer(st, 5);

    render_borders(base16);
    render_basket(base32, b, 1);
    render_round_timer(base16, rt);
    render_score(base16, score);
    render_start_timer(base16, st);

    while(score->value < 11 && rt->value > 0)
    {
        /* first move basket */
        render_basket(base32, b, -1);   
        move_basket(b, direction);
        b_collision = check_basket_collision(b, direction);
        if(b_collision == 0)
        {
            direction = -direction;
        }
        render_basket(base32, b, 1);
        /* then move apple */
        render_apple(base32, a, -1);
        move_apple(a);
        a_collision = check_apple_collision(b, a);
        if(a_collision > 0)
        {
            increment_score(score);
            render_score(base16, score);
            reset_apple_position(a);
        }
        if(a->y == 368)
        {
            reset_apple_position(a);
        }
        render_apple(base32, a, 1);

        fake_clock++;
        if(fake_clock == 70)
        {
            decrement_round_timer(base16, rt);
            fake_clock = 0;
        }

        Vsync();
    }
}