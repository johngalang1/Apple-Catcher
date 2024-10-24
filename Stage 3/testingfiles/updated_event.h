#ifndef MODEL_H
#define MODEL_H
#define NUM_LETTERS 20
#include "types.h"
#include "bitmaps.h"
#include "RASTER.H" 

/* 
AUTHORS: John G, Zach L
FILE NAME: model.h
PURPOSE: CONTAINS ALL OBJECTS AND BEHAVIOR FUNCTION PROTOTYPES FOR THE GAME
*/

typedef struct 
{
    UINT16 x, y;        /*Position of Apple*/
    UINT32 width;       
    UINT32 height;
} apple;

typedef struct
{ 
    UINT16 x, y;        /*Position of Basket*/
    int delta_x;        /*Horizontal displacement per clock tick*/
    UINT32 width;
    UINT32 height;
    UINT32 (*bitmap)[2]; /* Pointer to the basket bitmap */
} basket; 

typedef struct {
    UINT16 digit1_x, digit1_y;   /* Fixed position for digit 1 */
    UINT16 digit2_x, digit2_y;   /* Fixed position for digit 2 */
    UINT32 height;                     
    int value;                         /* Score value (integer < 60) */
} score;

typedef struct {
    UINT16 digit1_x, digit1_y;         /* Fixed position for digit 1 */
    UINT16 digit2_x, digit2_y;         /* Fixed position for digit 2 */
    UINT32 height;              
    int value;                         /* Timer value (integer <= 60) */
} timer_round;

typedef struct {
    UINT16 x, y;               
    UINT16 width;              
    UINT32 height;             
    int value;                 
    const UINT32 *digit_bitmaps[5];  /* Array of bitmaps for digits 5-1 */
} timer_start;


typedef struct {
    UINT16 start_x;   /* Starting x position for the message */
    UINT16 start_y;   /* Starting y position for the message */
    UINT16 spacing;   /* Spacing between characters */
    char *text;       /* String representing the message */
} message;

/* Functions */

/* Basket Function */
void move_basket(basket *b, int direction);

/* Apple Functions */
void move_apple(apple *a);
void generate_apple(apple *a);

/* Score Functions */
score *init_score();
void increment_score(UINT16 *base, score *curr_score);

/* Timer Functions */
timer_round *init_round_timer();
void decrement_round_timer(UINT16 *base, timer_round *t);
void decrement_start_timer(timer_start *t);


#endif;
