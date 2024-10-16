#ifndef model.h
#define model.h
#include "types.h"

typedef struct 
{
    UINT16 x, y;
    UINT32 width;
    UINT32 height;
} apple;

typedef struct
{ 
    UINT16 x, y; 
    int delta_x;
    UINT32 width;
    UINT32 height;
} basket; 

typedef struct {
    UINT16 digit1_x, digit1_y;  
    UINT16 digit2_x, digit2_y;  
    UINT16 width;               
    UINT32 height;              
    int value;                  
    const UINT16 *digit_bitmaps[10];  
} score;

typedef struct {
    UINT16 digit1_x, digit1_y;  
    UINT16 digit2_x, digit2_y;  
    UINT16 width;               
    UINT32 height;              
    int value;                  
    const UINT16 *digit_bitmaps[10];  
} timer_round;

typedef struct {
    UINT16 x, y;               
    UINT16 width;              
    UINT32 height;             
    int value;                 
    const UINT32 *digit_bitmaps[5];  
} timer_start;


typedef struct {
    UINT16 letter_x[NUM_LETTERS];   
    UINT16 letter_y[NUM_LETTERS];   
    const UINT16 *digit_bitmaps[NUM_LETTERS];  
} message;


#endif
