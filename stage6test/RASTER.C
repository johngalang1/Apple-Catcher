#include "raster.h"
/* 
AUTHORS: John G, Zach L
FILE NAME: RASTER.C
PURPOSE: CONTAINS FUNCTIONS FOR PLOTING OR CLEARING IMAGES/PIXELS TO THE SCREEN
*/

/* 
NAME: plot_apple_32
PARAMETERS: UINT32 *base - framebuffer, 
            UINT16 x - horizontal position of the screen, 
            int y - vertical position of the screen,
            const UINT32 *bitmap - bitmap of apple, 
            unsigned int height - height of apple
PURPOSE: To plot an apple onto the screen 
DETAILS: Calculates the starting memory address in the framebuffer to the given 
    x,y coordinates. Each row consists of 20, 32 pixel blocks. 
    The function then iterates over each row of the bitmap and writes it to the 
    correct position in the framebuffer. After plotting each row, the function 
    advances the framebuffer pointer by 20 to move down to the next screen row.
    The function only plots pixels that are within screen bounds meaning apples
    "move" onto the screen from negative y values and off the screen for y values > 400.
*/
void plot_apple_32(UINT32 *base, UINT16 x, int y,
                    const UINT32 *bitmap, unsigned int height)   
{
    int i = 0;    
    UINT16 k = y; 
    UINT32 *next = base + (k * 20) + (x >> 5);
    if (y < 0)
    {
        i = -y; 
        k = 0;  
        next = base + (x >> 5); 
    }
    while(i < height && k < SCREEN_HEIGHT)
    {
        *next = bitmap[i]; 
        i += 1;           
        k += 1;            
        next += 20;        
    }
}
/* 
NAME: plot_basket_64
PARAMETERS: *base - framebuffer, 
            int x - horizontal position of the screen, 
            int y - vertical position of the screen, 
            const UINT32 bitmap - bitmap of basket, 
            unsigned int height - height of basket 
PURPOSE: To plot the basket onto the screen 
DETAILS:  Calculates the starting memory address in the framebuffer to the given 
    x, y coordinates. Since each row of the screen is 640 pixels wide, the function adjusts the pointer 
    by dividing the screen width by 32. The basket bitmap is 64 pixels wide, so each row consists of 
    two `UINT32` values, stored in `bitmap[i][0]` and `bitmap[i][1]`. The function iterates through each row of the 
    bitmap, writing both parts of the row to the framebuffer. After plotting each row, it advances to the next line on the 
    screen and continues the process until all rows are plotted.
*/
void plot_basket_64(UINT32 *base, int x, int y, 
                    const UINT32 bitmap[BASKET_HEIGHT][2], unsigned int height)
{ 
    int i;
    UINT32 *next;
    
    for (i = 0; i < height; i++) {
        next = base + (y + i) * (20) + (x >> 5);
        *next = bitmap[i][0];
        *(next + 1) = bitmap[i][1];
    }
}
/* 
NAME: clear_screen
PARAMETERS: *base - framebuffer
PURPOSE: To clear the screen of any pixels that are currently existing
DETAILS: Fills every 32 bits with 0's for a total of 8000 iterations, since 
        (640 * 400) / 32 = 8000, effectively clearing the entire screen.
*/
void clear_screen(UINT32 *base)
{ 
    UINT32 clear_longword = (256000) >> 5; 
    int i; 

    for(i = 0; i < clear_longword; i++)
    { 
        base[i] = 0x00000000;
    }
}

/*
 NAME: plot_vertical_line
 PARAMETERS: *base - framebuffer 
             int x - horizontal position of the screen,
             int n - y value to start, 
             int m - y value to stop
 PURPOSE: To plot a vertical line 1-pixel thick on the screen
 DETAILS: Plots a 1-pixel thick vertical line at an x value (where 0 <= X < SCREEN_WIDTH),
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
PARAMETERS: UINT16 *base - framebuffer 
            int x - horizontal position of the screen,
            int y - vertical position of the screen
PURPOSE: Plots an individual pixel on the screen 
DETAILS: The expression (1 << (15 - (x & 15))) is used to calculate which bit 
         to set within the word, ensuring the correct pixel is modified.
*/
void plot_pixel(UINT16 *base, int x, int y)
{
    *(base + y * 40 + (x >> 4)) |= 1 << (15 - (x & 15));
}

/*
NAME: plot_char
PARAMETERS: UINT16 *base - framebuffer
            int x - horizontal position of the screen,
            int y - vertical position of the screen,
            const UINT16 *bitmap - bitmap of character,
            unsigned int height - height of character
PURPOSE: Plots a character bitmap on the screen at the specified (x, y) coordinates.
DETAILS: Calculates the starting memory address in the framebuffer to the given 
    x,y coordinates. Each row consists of 40, 16 pixel blocks. 
    The function then iterates over each row of the bitmap and writes it to the 
    correct position in the framebuffer. After plotting each row, the function 
    advances the framebuffer pointer by 40 to move down to the next screen row.
*/
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

/*
NAME: clear_basket
PARAMETERS: UINT32 *base - framebuffer
            int x - horizontal screen position,
            int y - vertical screen position,
            unsigned int width - width of the basket,
            unsigned int height - height of the basket
PURPOSE: Clears the area occupied by the basket
DETAILS: Calculates the starting address in the framebuffer using (x, y). Each row consists 
    of 20 blocks of 32 pixels. The function clears the bitmap array based on the basket's width. 
    After clearing a row, the pointer advances by 20 to move to the next row.
*/

void clear_basket(UINT32 *base, int x, int y, unsigned int width, unsigned int height)
{
    UINT32 *next = base + (y * 20) + (x >> 5);
    int i;

    for (i = 0; i < height; i++)
    {
        next[0] = 0x00000000;  
        if (width > 32)
        {
            next[1] = 0x00000000;  
        }
        next += 20;  
    }
}

/*
NAME: clear_apple
PARAMETERS: UINT32 *base - framebuffer,
            int x - horizontal screen position,
            int y - vertical screen position,
            unsigned int width - width of the apple,
            unsigned int height - height of the apple
PURPOSE: Clears the area occupied by the apple
DETAILS: Calculates the starting address in the framebuffer using (x, y). Each row consists 
        of 20 blocks of 32 pixels. The function clears one 32-bit longword for each row. After 
        clearing a row, the pointer advances by 20 to move to the next row.
*/

void clear_apple(UINT32 *base, int x, int y, unsigned int width, unsigned int height)
{ 
    UINT32 *next; 
    int i; 

    if (y < 0) {
        height += y; 
        y = 0;     
    }

    /* Ensure the starting coordinates are valid */
    if (x < 0 || y < 0 || y + height > SCREEN_HEIGHT) return;

    next = base + (y * 20) + (x >> 5);  

    for (i = 0; i < height; i++)
    {
        *next = 0x00000000;  /* Set all 32 pixels in this row to black */
        next += 20;          /* Move to the next row in the buffer */
    }
}

/*
NAME: clear_char
PARAMETERS: UINT16 *base - framebuffer,
            int x - horizontal screen position,
            int y - vertical screen position,
            unsigned int height - height of the character
PURPOSE: Clears the area occupied by a character
DETAILS: Calculates the starting address in the framebuffer using (x, y). Each row contains 
    40 blocks of 16 pixels. The function clears one 16-bit word for each row. After 
    clearing a row, the pointer advances by 40 to move to the next row.
*/
void clear_char(UINT16 *base, int x, int y, unsigned int height)
{
    UINT16 *next = base + (y * 40) + (x >> 4);
    int i = 0;
    while (i < height)
    {
        next[0] = 0x0000;
        next += 40;
        i++;
    }
}
