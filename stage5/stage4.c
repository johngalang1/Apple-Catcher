#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include "renderer.h"
#include "driver.h" 
#include "input.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: stage4.c
PURPOSE: CONTAINS RENDER TESTING FOR STAGE 4
*/

int main()
{
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    char input;
    model *curr_model = init_model();
    clear_screen(FB32); 
    input_init();

    while ( input != 'Q')
    {
        printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple movement\n 3. score rendering\n"
       " 4. a single frame render(press a key to end)\n 5. master render including countdown timer(press a key to count down)\n Q - Quit\n");
        input = Cnecin();

        switch (input)
        {
            case '1':
                test_basket_render(FB32, FB16, &(curr_model->b));  
                break;

            case '2':
                test_apple_render(FB32, FB16, &(curr_model->apples[0]), &(curr_model->b)); 
                break;

            case '3':
                test_score_render(FB32, FB16, &(curr_model->apples[0]), &(curr_model->b), &(curr_model->curr_score));  
                break;
            
            case '4':
                test_frame_render(FB32, FB16, curr_model); 
                break;

            case '5':
                test_master_render(FB32, FB16, &(curr_model->apples[0]), &(curr_model->b),
                        &(curr_model->curr_score), &(curr_model->rt), &(curr_model->st)); 
                break;
            default:
                break;
        }
    }
    return 0;
}
