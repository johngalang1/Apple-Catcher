#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include "driver.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: stage3.c
PURPOSE: TESTS ALL FUNCTIONS FOR STAGE 3
*/

int main()
{
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    char input;
    
    clear_screen(FB32);
    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");

    while ( input != 'Q')
    {
        input = Cnecin();

        switch (input)
        {
            case '1':
                test_basket_movement();  
                break;

            case '2':
                test_apple_collision(); 
                break;

            case '3':
                test_random_apple_position();  
                break;
            
            case '4':
                test_basket_right_border_collision(); 
                break;

            case '5':
                test_basket_left_border_collision(); 
                break;
            case '6':
                test_apple_movement();  
                break;
            case '7':
                test_score_increment(); 
                break;
            case '8': 
                test_timer_decrement();
                break;
            case '9': 
                test_display_message();
                break;
            default:
                break;
        }
    }

    return 0;
}
