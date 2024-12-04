#include "effects.h"
#include "PSG.h" 


/* 
AUTHORS: John G, Zach L
FILE NAME: effects.c
PURPOSE: CONTAINS FUNCTIONS FOR SOUND EFFECTS
*/

/*
NAME: point_sound
PARAMETERS: None
PURPOSE: Plays a sound effect when a point is gained.
*/
void play_score() {
    int i;

    /* Set up the sound */
    set_tone(2, 198);  
    set_volume(2, 12);         
    enable_channel(2, 1, 0);    
}


/*
NAME: splat_sound
PARAMETERS: None
PURPOSE: Plays a sound effect when the apple hits the bottom of the screen.
*/

void play_splat() {
    int i;   
    set_tone(2, 451);        
    set_noise(12);
    set_volume(2, 12);        
    enable_channel(2, 1, 1);      
}
