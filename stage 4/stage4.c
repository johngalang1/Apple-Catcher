#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include "renderer.h"
#include "driver.h"

int main()
{
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    char input;
    basket *p_basket = init_basket();
    timer_round *r_timer = init_round_timer();
    score *curr_score = init_score();
    timer_start *s_timer = init_start_timer();
    generate_apple(3);  
    generate_apple(6);
    clear_screen(FB32);
    /* testing starts here */


    while ( input != 'Q')
    {
        printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple movement\n 3. score rendering\n"
       " 4. a single frame render(press a key to end)\n 5. master render including countdown timer(press a key to count down)\n Q - Quit\n");
        input = Cnecin();

        switch (input)
        {
            case '1':
                test_basket_render(FB32, FB16, p_basket);  
                break;

            case '2':
                test_apple_render(FB32, FB16, &apples[0], p_basket); 
                break;

            case '3':
                test_score_render(FB32, FB16, &apples[0], p_basket, curr_score);  
                break;
            
            case '4':
                test_frame_render(FB32, FB16, &apples[0], p_basket,
                        curr_score, r_timer); 
                break;

            case '5':
                test_master_render(FB32, FB16, &apples[0], p_basket,
                        curr_score, r_timer, s_timer); 
                break;
            default:
                break;
        }
    }
    return 0;
}
