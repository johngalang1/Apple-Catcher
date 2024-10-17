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
    UINT16 digit1_x, digit1_y;         /* Fixed position for digit 1 */
    UINT16 digit2_x, digit2_y;         /* Fixed position for digit 2 */
    UINT16 width;               
    UINT32 height;                     /* Score value (integer < 60) */
    int value;                  
    const UINT16 *digit_bitmaps[10];   /* Array of bitmaps for digits 0-9 */
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




#endif
