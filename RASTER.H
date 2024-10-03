#ifndef RASTER_H
#define RASTER_H

#include "types.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: RASTER.H 
PURPOSE: CONTAINS ALL FUNCTION HEADERS USED FOR THE PROGRAM INCLUDING: 
        - Plot Basket 
        - Plot Apple 
        - Clear Screen 
        - Plot Vertical Line 
        - Plot Horizontal Line
*/
void plot_basket_64(UINT32 *base, int x, int y, 
                    const UINT32 *bitmap[BASKET_HEIGHT][2], unsigned int height); 

void plot_apple_32(UINT32 *base, int x, int y, 
                    const UINT32 *bitmap, unsigned int height);

void clear_screen(UINT32 *base);

void plot_vertical_line(UINT32 *base, int x, int n, int m);

#endif
