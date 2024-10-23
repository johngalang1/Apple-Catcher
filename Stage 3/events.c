#include "events.h"


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

void increment_score(UINT16 *base, score *curr_score)
{ 
    curr_score->value += 1;
    update_score(base, curr_score);
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
void decrement_round_timer(UINT16 *base, timer_round *t)
{
    t->value -= 1;
    update_round_timer(base, t);
}

