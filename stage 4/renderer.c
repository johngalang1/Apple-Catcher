#include "renderer.h"


void render_apple(UINT32 *base, apple *a, int op)
{
    if(op == 1)
    {
        plot_apple_32(base, a->x, a->y, apple_bitmap, APPLE_HEIGHT);

    }
    else
    {
        clear_apple(base, a->x, a->y, a->width, a->height);
    }
}

void render_basket(UINT32 *base, basket *b, int op)
{
    if(op == 1)
    {
        plot_basket_64(base, b->x, b->y, basket_bitmap, BASKET_HEIGHT);
    }
    else
    {
        clear_basket(base, b->x, b->y, b->width, b->height);
    }
}


void render_score(UINT16 *base, score *score)
{
    int digit_1, digit_2; /*digit 1 is ones digit, digit 2 is tens digit*/
    digit_1 = score->value % 10;
    digit_2 = score->value / 10;

    clear_char(base, score->digit1_x, score->digit1_y, CHARACTER_HEIGHT);
    plot_char(base, score->digit1_x, score->digit1_y, num_maps[digit_1], CHARACTER_HEIGHT);
    clear_char(base, score->digit2_x, score->digit2_y, CHARACTER_HEIGHT);
    plot_char(base, score->digit2_x, score->digit2_y, num_maps[digit_2], CHARACTER_HEIGHT);
}

void render_round_timer(UINT16 *base, timer_round *rt)
{
    int digit_1, digit_2;   /* digit 1 is ones digit, digit 2 is tens digit */
    digit_1 = rt->value % 10;
    digit_2 = rt->value / 10;

    clear_char(base, rt->digit1_x, rt->digit1_y, CHARACTER_HEIGHT);
    plot_char(base, rt->digit1_x, rt->digit1_y, num_maps[digit_1], CHARACTER_HEIGHT);
    clear_char(base, rt->digit2_x, rt->digit2_y, CHARACTER_HEIGHT);
    plot_char(base, rt->digit2_x, rt->digit2_y, num_maps[digit_2], CHARACTER_HEIGHT);
}

void render_start_timer(UINT16 *base, timer_start *st)
{
    while(st->value > 0)
    {
        clear_char(base, st->x, st->y, st->height);
        plot_char(base, st->x, st->y, num_maps[st->value], st->height);
        Cnecin();
        st->value -= 1;
    }
    clear_char(base, st->x, st->y, st->height);
    plot_char(base, st->x, st->y, letterG_bitmap, st->height);
    plot_char(base, st->x + 16, st->y, letterO_bitmap, st->height);
    Cnecin();
    clear_char(base, st->x, st-> y, st->height);
    clear_char(base, st->x + 16, st->y, st->height);
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
    UINT16 *FB16 = Physbase();
    int i = 0;
    while (msg->text[i] != '\0') {
        const UINT16 *bitmap = get_bitmap_for_char(msg->text[i]);
        
        if (bitmap) {
            clear_char(Physbase(), msg->start_x + i * msg->spacing, msg->start_y, CHARACTER_HEIGHT);
        }
        
        i++;
    }
}

void render_borders(UINT16 *base)
{
    plot_vertical_line(base, LEFT_BORDER, 0, 399);
    plot_vertical_line(base, RIGHT_BORDER, 0, 399);
}

void master_render(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt)
    {
        render_apple(base32, a, 1);
        render_basket(base32, b, 1);
        render_score(base16, score);
        render_round_timer(base16, rt);
    }
