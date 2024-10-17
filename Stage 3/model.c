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

/* none of these work yet because I am having issues with init score in main */
score init_score()
{
    score game_score;
        game_score.digit1_x = 32; /* ones digit */
        game_score.digit1_y = 16;
        game_score.digit2_x = 16; /* tens digit */
        game_score.digit2_y = 16;
        game_score.height = CHARACTER_HEIGHT;
        game_score.value = 0;
    return game_score;
}

void increment_score(UINT16 *base, score curr_score)
{
    curr_score.value += 1;
    update_score(base, curr_score);
}

void update_score(UINT16 *base, score curr_score)
{
    int digit_1, digit_2; /*digit 1 is ones digit, digit 2 is tens digit*/
    digit_1 = curr_score.value % 10;
    digit_2 = curr_score.value / 10;

    clear_char(base, curr_score.digit1_x, curr_score.digit1_y, CHARACTER_HEIGHT);
    plot_char(base, curr_score.digit1_x, curr_score.digit1_y, num_maps[digit_1], CHARACTER_HEIGHT);
    clear_char(base, curr_score.digit2_x, curr_score.digit2_y, CHARACTER_HEIGHT);
    plot_char(base, curr_score.digit2_x, curr_score.digit2_y, num_maps[digit_2], CHARACTER_HEIGHT);
}
