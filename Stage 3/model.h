#ifndef model.h
#define model.h
#define NUM_LETTERS 20
#include "types.h"

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
} basket; 

typedef struct {
    const UINT16 digit1_x, digit1_y;   /* Fixed position for digit 1 */
    const UINT16 digit2_x, digit2_y;   /* Fixed position for digit 2 */
    UINT32 height;                     
    int value;                         /* Score value (integer < 60) */
} score;

typedef struct {
    UINT16 digit1_x, digit1_y;         /* Fixed position for digit 1 */
    UINT16 digit2_x, digit2_y;         /* Fixed position for digit 2 */
    UINT16 width;               
    UINT32 height;              
    int value;                         /* Timer value (integer <= 60) */
    const UINT16 *digit_bitmaps[10];   /* Array of bitmaps for digits 0-9 */
} timer_round;

typedef struct {
    UINT16 x, y;               
    UINT16 width;              
    UINT32 height;             
    int value;                 
    const UINT32 *digit_bitmaps[5];  /* Array of bitmaps for digits 5-1 */
} timer_start;


typedef struct {
    UINT16 letter_x[NUM_LETTERS];   /* Array of x positions for each letter */
    UINT16 letter_y[NUM_LETTERS];   /* Array of y positions for each letter */
    const UINT16 *digit_bitmaps[NUM_LETTERS];  /* Array of bitmaps, one for each character in the message */
} message;


/* Functions */

void move_basket(basket *b, int direction);
void check_basket_collision(basket *b);

/* Apple Functions */
void move_apple(apple *a);
int check_apple_collision(basket *b, apple *a);
void reset_apple(apple *a);

/* Score Functions */
void update_score(score *s);

/* Timer Functions */
void decrement_timer(timer_round *t);
int is_time_up(timer_round *t);

void decrement_start_timer(timer_start *t);
int is_start_time_up(timer_start *t);

/* Message Functions */ 
void display_message(message *msg);
void clear_message(message *msg);



#endif
