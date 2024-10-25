#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "bitmaps.h"
/* 
AUTHORS: John G, Zach L 
FILE NAME: stage2.c
PURPOSE: TESTING FOR PLOTTING AND CLEARING BITMAPS
*/

int main() {
    UINT32 *FB32 = Physbase();
    UINT16 *FB16 = Physbase();
    char input = '\0';

    /* Test Loop */
    while (input != 'Q') {
        printf("\nPress Numbers to Test:\n"
               " 1. Plot Apple\n"
               " 2. Plot Basket\n"
               " 3. Plot Character A\n"
               " 4. Clear Screen\n"
               " 5. Plot Vertical Line\n"
               " 6. Plot Pixel\n"
               " Q - Quit\n");
			
        input = Cnecin();

        switch (input) {
            case '1':
				printf("Plotted Apple. Press any key to clear.\n");
                plot_apple_32(FB32, 400, 300, apple_bitmap, APPLE_HEIGHT);
                Cnecin();  
                clear_apple(FB32, 400, 300, 32, APPLE_HEIGHT);
                printf("Apple Cleared\n");
                break;

            case '2':
				printf("Plotted Basket. Press any key to clear.\n");
                plot_basket_64(FB32, 400, 350, basket_bitmap, BASKET_HEIGHT);
                Cnecin();  
                clear_basket(FB32, 400, 350, 64, BASKET_HEIGHT);
                printf("Basket Cleared\n");
                break;

            case '3':
				printf("Plotted Character A. Press any key to clear.\n");
                plot_char(FB16, 400, 300, letterA_bitmap, CHARACTER_HEIGHT);
                Cnecin();  
                clear_char(FB16, 400, 300, CHARACTER_HEIGHT);
                printf("Character A Cleared\n");
                break;

            case '4':
                clear_screen(FB32);
                printf("Screen Cleared\n");
                break;

            case '5':
				printf("Vertical Line Plotted. Press any key to clear.\n");
                plot_vertical_line(FB16, 400, 0, 400);
                Cnecin();   
                clear_screen(FB32);  
                printf("Vertical Line Cleared\n");
                break;

            case '6':
                printf("Pixel Plotted. Press any key to clear.\n");
				plot_pixel(FB16, 300, 300);
                Cnecin(); 
                clear_screen(FB32);  
                printf("Pixel Cleared\n");
                break;

            default:
                break;
        }
    }

    return 0;
}
