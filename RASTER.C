#include "raster.h"

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
