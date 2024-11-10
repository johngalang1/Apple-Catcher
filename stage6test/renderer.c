#include "renderer.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: renderer.c
PURPOSE: CONTAINS FUNCTIONS FOR RENDERING IMAGES ON THE SCREEN
*/

/*
NAME: render_apple
PARAMETERS: *base - framebuffer, 
            *a - pointer to the apple structure, 
            op - operation (1 to plot, otherwise clear)
PURPOSE: To render or clear an apple on the screen based on the specified operation.
DETAILS: Plots the apple if `op` is 1; otherwise, clears the apple from its current position.
*/
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

/*
NAME: render_basket
PARAMETERS: 
    *base - framebuffer
    *b - pointer to the basket structure
    op - operation (1 to plot, otherwise clear)
PURPOSE: To render or clear a basket on the screen based on the specified operation.
DETAILS: Plots the basket if `op` is 1; otherwise, clears the basket from its current position.
*/
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

/*
NAME: render_score
PARAMETERS: 
    *base - framebuffer
    *score - pointer to the score structure
PURPOSE: To display the current score on the screen by plotting the ones and tens digits.
DETAILS: Clears the previous score display and plots the updated digits at specified coordinates using `num_maps`.
*/
void render_score(UINT16 *base, score *score)
{
    int digit_1, digit_2; 
    digit_1 = score->value % 10;
    digit_2 = score->value / 10;

    clear_char(base, score->digit1_x, score->digit1_y, CHARACTER_HEIGHT);
    plot_char(base, score->digit1_x, score->digit1_y, num_maps[digit_1], CHARACTER_HEIGHT);
    clear_char(base, score->digit2_x, score->digit2_y, CHARACTER_HEIGHT);
    plot_char(base, score->digit2_x, score->digit2_y, num_maps[digit_2], CHARACTER_HEIGHT);
}

/*
NAME: render_round_timer
PARAMETERS: 
    *base - framebuffer
    *rt - pointer to the round timer structure
PURPOSE: To display the current round timer value on the screen by plotting the ones and tens digits.
DETAILS: Clears the previous timer display and plots the updated digits at specified coordinates using `num_maps`.
*/
void render_round_timer(UINT16 *base, timer_round *rt)
{
    int digit_1, digit_2;   
    digit_1 = rt->value % 10;
    digit_2 = rt->value / 10;

    clear_char(base, rt->digit1_x, rt->digit1_y, CHARACTER_HEIGHT);
    plot_char(base, rt->digit1_x, rt->digit1_y, num_maps[digit_1], CHARACTER_HEIGHT);
    clear_char(base, rt->digit2_x, rt->digit2_y, CHARACTER_HEIGHT);
    plot_char(base, rt->digit2_x, rt->digit2_y, num_maps[digit_2], CHARACTER_HEIGHT);
}

/*
NAME: render_start_timer
PARAMETERS: 
    *base - framebuffer
    *st - pointer to the start timer structure
PURPOSE: To display a countdown timer on the screen, decrementing until zero and then displaying "GO".
DETAILS: Clears and plots each countdown value at specified coordinates, and displays "GO" when the countdown completes.
*/
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
        default: return NULL;  
    }
}

/*
NAME: display_message
PARAMETERS: *msg - pointer to the message structure
PURPOSE: To display a specified message on the screen at given coordinates.
DETAILS: Iterates through each character in the message, retrieves its bitmap, 
        and plots it on the screen with defined spacing.
*/
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

/*
NAME: clear_message
PARAMETERS: *msg - pointer to the message structure
PURPOSE: To remove a displayed message from the screen.
DETAILS: Iterates through each character in the message and clears it from the screen at specified coordinates.
*/
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

/*
NAME: master_render
PARAMETERS: 
    *base32 - framebuffer (32-bit)
    *base16 - framebuffer (16-bit)
    *a - pointer to the apple structure
    *b - pointer to the basket structure
    *score - pointer to the score structure
    *rt - pointer to the round timer structure
PURPOSE: To render the apple, basket, score, and round timer on the screen.
DETAILS: Calls individual render functions to display each game element at their respective positions.
*/
void master_render(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt)
    {
        render_apple(base32, a, 1);
        render_basket(base32, b, 1);
        render_score(base16, score);
        render_round_timer(base16, rt);
    }

void render_model(UINT32 *base32, UINT16 *base16, apple *a, basket *b,
                        score *score, timer_round *rt, timer_start *st) 
{ 
    /* Initial setup */
    clear_screen(base32);
    set_basket(b, 448);
    set_apple(a, 384, -32);
    reset_score(score);
    set_round_timer(rt, 60);
    /*set_start_timer(st, 5); */

    render_borders(base16);
    render_basket(base32, b, 1);
    render_round_timer(base16, rt);
    render_score(base16, score);
    /* render_start_timer(base16, st); */
}

/* Initializes model before game starts*/
void initialize_model(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt)
{ 
    set_basket(b, 320); 
    set_apple(a, 384, -32);
    reset_score(score);
    set_round_timer(rt, 60);

    render_basket(base32, b, 1);
    render_apple(base32, a, 1);
    render_round_timer(base16, rt);
    render_score(base16, score);

}

/* Updates game between buffers */
void update_model(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt)
{ 
    render_basket(base32, b, 1);
    render_apple(base32, a, 1);
    render_round_timer(base16, rt);
    render_score(base16, score);
}        

/* Function to render objects to a specified buffer */
void render_objects(UINT32 *buffer, model *curr_model, int a_collision) {
    /* Render basket to specified buffer */
    render_basket(buffer, &(curr_model->b), -1);  /* Clear previous position */
    move_basket_based_on_input(&(curr_model->b));
    render_basket(buffer, &(curr_model->b), 1);   /* Render new position */

    /* Render apple to specified buffer */
    render_apple(buffer, &(curr_model->apples[0]), -1);  /* Clear previous position */
    move_apple(&(curr_model->apples[0]));
    if (a_collision > 0) {
        increment_score(&(curr_model->curr_score));
        render_score((UINT16*) buffer, &(curr_model->curr_score));
        reset_apple_position(&(curr_model->apples[0]));
    }
    if (curr_model->apples[0].y == 368) {
        reset_apple_position(&(curr_model->apples[0]));
    }
    render_apple(buffer, &(curr_model->apples[0]), 1);  /* Render new apple position */
}