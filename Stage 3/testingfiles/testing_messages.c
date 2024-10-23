#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"

int main()
{
    /* Initialize framebuffer, timers, etc. */
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = Physbase();

    /* Define a message struct */
    message game_message;
    game_message.start_x = 100;  /* Starting x position */
    game_message.start_y = 50;   /* Starting y position */
    game_message.spacing = 16;   /* Spacing between letters */
    game_message.text = "CHICKEN BUTT"; /* The message text */
    
    clear_screen(FB32);
    
    /* Display the message before the game starts */
    display_message(&game_message);
    
    /* Wait for input before clearing the message */
    Cnecin();  /* Wait for input */
    
    /* Clear the message */
    clear_message(&game_message);
    
    /* Your game logic and loop can go here */
    
    return 0;
}
