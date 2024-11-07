#include "driver.h"
#include <osbind.h>

/* 
AUTHORS: John G, Zach L
FILE NAME: driver.c
PURPOSE: CONTAINS FUNCTIONS FOR TESTING RENDERING
*/

void render_model(UINT32 *base32, UINT16 *base16, apple *a, basket *b,
                        score *score, timer_round *rt, timer_start *st) 
{ 
    /* Initial setup */
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
}