#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include "driver.h"

int main()
{
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    char input;
    
    clear_screen(FB32);
    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");


    /* Game Loop for Testing */
    while ( input != 'Q')
    {
        input = Cnecin();  /* Get user input */

        switch (input)
        {
            case '1':
                test_basket_movement();  /* Test basket movement */
                break;

            case '2':
                test_apple_collision();  /* Test apple collision */
                break;

            case '3':
                test_random_apple_position();  /* Test random apple position */
                break;
            
            case '4':
                test_basket_right_border_collision();  /* Test basket collision with the right border */
                break;

            case '5':
                test_basket_left_border_collision();  /* Test basket collision with the left border */
                break;
            case '6':
                test_apple_movement();  /* Test apple movement */
                break;
            case '7':
                test_score_increment();  /* Test score incrementer */
                break;
            case '8': 
                test_timer_decrement();
                break;
            case '9': 
                test_display_message();
                break;


            default:
                /* Ignore any other input */
                break;
        }

        /* Small delay between tests */
        Vsync();
    }

    return 0;
}
