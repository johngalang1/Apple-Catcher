#include "driver.h"
#include <osbind.h>

/* a simple loop to render the basket and move it from right to left a couple times */
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

/* drops a couple apples */
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