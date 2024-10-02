#include "raster.h"

/* 
NAME: plot_basket_32
PARAMETERS: *base (framebuffer), x position of the screen, y position of the screen, 
            bitmap of apple, height of apple
PURPOSE: To plot an apple onto the screen 
DETAILS: 
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
PARAMETERS: *base (framebuffer), x position of the screen, y position of the screen, 
            bitmap of basket, height of basket 
PURPOSE: To plot the basket onto the screen 
DETAILS: 
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
DETAILS: Fills every 32 bits with 0's for a total of 8000 iterations, 
        effectively clearing the entire screen
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
