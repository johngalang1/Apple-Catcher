#include <stddef.h>  
#include <osbind.h>  
#include "events.h"
#include "raster.h"


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

/* MESSAGE FUNCTIONS */
/* Function to map a character to its corresponding bitmap */
const UINT16 *get_bitmap_for_char(char c) {
    switch (c) {
        case 'A': return letterA_bitmap;
        case 'B': return letterB_bitmap;
        case 'C': return letterC_bitmap;
        case 'D': return letterD_bitmap;
        case 'E': return letterE_bitmap;
        case 'F': return letterF_bitmap;
        case 'G': return letterG_bitmap;
        case 'H': return letterH_bitmap;
        case 'I': return letterI_bitmap;
        case 'J': return letterJ_bitmap;
        case 'K': return letterK_bitmap;
        case 'L': return letterL_bitmap;
        case 'M': return letterM_bitmap;
        case 'N': return letterN_bitmap;
        case 'O': return letterO_bitmap;
        case 'P': return letterP_bitmap;
        case 'Q': return letterQ_bitmap;
        case 'R': return letterR_bitmap;
        case 'S': return letterS_bitmap;
        case 'T': return letterT_bitmap;
        case 'U': return letterU_bitmap;
        case 'V': return letterV_bitmap;
        case 'W': return letterW_bitmap;
        case 'X': return letterX_bitmap;
        case 'Y': return letterY_bitmap;
        case 'Z': return letterZ_bitmap;
        default: return NULL;  /* Return NULL if the character is not supported */
    }
}

/* Function to display the message */
void display_message(const message *msg) {
    int i = 0;
    while (msg->text[i] != '\0') {  /* Iterate through the text until the null terminator */
        const UINT16 *bitmap = get_bitmap_for_char(msg->text[i]);
        
        if (bitmap) {  /* If a valid bitmap is found for the character */
            plot_char(Physbase(), msg->start_x + i * msg->spacing, msg->start_y, bitmap, CHARACTER_HEIGHT);
        }
        
        i++;  /* Move to the next character */
    }
}

/* Function to clear the message from the screen */
void clear_message(const message *msg) {
    int i = 0;
    while (msg->text[i] != '\0') {
        const UINT16 *bitmap = get_bitmap_for_char(msg->text[i]);
        
        if (bitmap) {
            clear_char(Physbase(), msg->start_x + i * msg->spacing, msg->start_y, CHARACTER_HEIGHT);
        }
        
        i++;
    }
}

