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

/* score functions */

score *init_score()
{
    static score game_score;
        game_score.digit1_x = 32; /* ones digit */
        game_score.digit1_y = 16;
        game_score.digit2_x = 16; /* tens digit */
        game_score.digit2_y = 16;
        game_score.height = CHARACTER_HEIGHT;
        game_score.value = 0;
    return &game_score;
}

void increment_score(UINT16 *base, score *curr_score)
{
 
    curr_score->value += 1;
    update_score(base, curr_score);
}

void update_score(UINT16 *base, score *curr_score)
{
    int digit_1, digit_2; /*digit 1 is ones digit, digit 2 is tens digit*/
    digit_1 = curr_score->value % 10;
    digit_2 = curr_score->value / 10;

    clear_char(base, curr_score->digit1_x, curr_score->digit1_y, CHARACTER_HEIGHT);
    plot_char(base, curr_score->digit1_x, curr_score->digit1_y, num_maps[digit_1], CHARACTER_HEIGHT);
    clear_char(base, curr_score->digit2_x, curr_score->digit2_y, CHARACTER_HEIGHT);
    plot_char(base, curr_score->digit2_x, curr_score->digit2_y, num_maps[digit_2], CHARACTER_HEIGHT);
}

/* round timer functions */

timer_round *init_round_timer()
{
    static timer_round t;
        t.digit1_x = 608; /* ones digit */
        t.digit1_y = 16;
        t.digit2_x = 592; /* tens digit */
        t.digit2_y = 16;
        t.height = CHARACTER_HEIGHT;
        t.value = 60; 
    return &t;
}

void decrement_round_timer(UINT16 *base, timer_round *t)
{
    t->value -= 1;
    update_round_timer(base, t);
}

void update_round_timer(UINT16 *base, timer_round *t)
{
    int digit_1, digit_2;   /* digit 1 is ones digit, digit 2 is tens digit */
    digit_1 = t->value % 10;
    digit_2 = t->value / 10;

    clear_char(base, t->digit1_x, t->digit1_y, CHARACTER_HEIGHT);
    plot_char(base, t->digit1_x, t->digit1_y, num_maps[digit_1], CHARACTER_HEIGHT);
    clear_char(base, t->digit2_x, t->digit2_y, CHARACTER_HEIGHT);
    plot_char(base, t->digit2_x, t->digit2_y, num_maps[digit_2], CHARACTER_HEIGHT);
}
