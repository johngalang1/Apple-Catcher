#include "raster.h"
/* 
AUTHORS: John G, Zach L
FILE NAME: RASTER.C
PURPOSE: CONTAINS ALL DEVELOPED FUNCTIONS
*/

/* 
NAME: plot_basket_32
PARAMETERS: *base (framebuffer), 
            x position of the screen, 
            y position of the screen, 
            bitmap of apple, 
            height of apple
PURPOSE: To plot an apple onto the screen 
DETAILS: Calculates the starting memory address in the framebuffer to the given 
    x,y coordinates. Each row consists of 20, 32 pixel blocks. 
    The function then iterates over each row of the bitmap and writes it to the 
    correct position in the framebuffer. After plotting each row, the function 
    advances the framebuffer pointer by 20 to move down to the next screen row.
*/
void plot_apple_32(UINT32 *base, int x, int y, 
                    const UINT32 *bitmap, unsigned int height)
{ 
    UINT32 *next = base + (y * 20) + ( x >> 5); 
    int i = 0;      

    while(i < height)
    { 
        *next = bitmap[i]; 
        next += 20; 
        i += 1;
    } 
} 
/* 
NAME: plot_basket_64
PARAMETERS: *base (framebuffer), 
            x position of the screen, 
            y position of the screen, 
            bitmap of basket, 
            height of basket 
PURPOSE: To plot the basket onto the screen 
DETAILS:  Calculates the starting memory address in the framebuffer to the given 
    x, y coordinates. Since each row of the screen is 640 pixels wide, the function adjusts the pointer 
    by dividing the screen width by 32 (as each `UINT32` holds 32 pixels). The basket bitmap is 64 pixels 
    wide, so each row consists of two `UINT32` values, stored in `bitmap[i][0]` and `bitmap[i][1]`. 
    The function iterates through each row of the bitmap, writing both parts of the row to the framebuffer. 
    After plotting each row, it advances to the next line on the screen and continues the process until all rows are plotted.
*/
void plot_basket_64(UINT32 *base, int x, int y, 
                    const UINT32 *bitmap[BASKET_HEIGHT][2], unsigned int height)
{ 
    int i;
    UINT32 *next;
    
    for (i = 0; i < height; i++) {
        next = base + (y + i) * (SCREEN_WIDTH >> 5) + (x >> 5);
        *next = bitmap[i][0];
        *(next + 1) = bitmap[i][1];
    }
}
/* 
NAME: clear_screen
PARAMETERS: *base (framebuffer)
PURPOSE: To clear the screen of any pixels that are currently existing
DETAILS: Fills every 32 bits with 0's for a total of 8000 iterations, since 
        (640 * 400) / 32 = 8000, effectively clearing the entire screen
*/
void clear_screen(UINT32 *base)
{ 
    UINT32 clear_longword = (SCREEN_WIDTH * SCREEN_HEIGHT) >> 5; 
    int i; 

    for(i = 0; i < clear_longword; i++)
    { 
        base[i] = 0x00000000;
    }
}

/*
 NAME: plot_vertical_line
 PARAMETERS: *base (framebuffer), int x (x location to be plotted), int n(y value to start), int m(y value to stop)
 PURPOSE: to plot a vertical line 1-pixel thick on the screen
 DETAILS: plots a 1-pixel thick vertical line at an x value (where 0 <= X < SCREEN_WIDTH),
            starts at y = n and ends at y = m.
 */
void plot_vertical_line(UINT16 *base, int x, int n, int m)
{
    int i;
    int dif = m-n;
    for(i = 0; i <dif; i++)
    {
        plot_pixel(base, x, n);
        n++;
    }
}

/*
NAME: plot_pixel
PARAMETERS: UINT16 *base (framebuffer), int x (x axis), int y (y axis)
purpose: used to plot an individual pixel
*/
void plot_pixel(UINT16 *base, int x, int y)
{
    *(base + y * 40 + (x >> 4)) |= 1 << (15 - (x & 15));
}


void plot_char(UINT16 *base, int x, int y, 
                const UINT16 *bitmap, unsigned int height)
{ 
    UINT16 *next = base + (y * 40) + ( x >> 4); 
    int i = 0;      

    while(i < height)
    { 
        *next = bitmap[i]; 
        next += 40; 
        i += 1;
    } 
}
