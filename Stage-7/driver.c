#include "driver.h"
#include <stdio.h>
 
/* 
AUTHORS: John G, Zach L
FILE NAME: driver.c
PURPOSE: CONTAINS FUNCTIONS FOR TESTING
*/

/*
 * Function: test_psg_routines
 * Purpose: Tests the basic functionality of the PSG low-level routines.
 *          Writes values to PSG registers and verifies them using reads.
 */
void test_psg_routines() {

    int reg = 0; 
    UINT8 test_value = 123; 
    UINT8 read_value; 

    printf("Testing PSG routines...\n");

    /* Write the value to the PSG register */
    write_psg(reg, test_value);
    printf("Wrote value %d to register %d.\n", test_value, reg);

    /* Read back the value from the PSG register */
    read_value = read_psg(reg);
    printf("Read value %d from register %d.\n", read_value, reg);

    /* Check if the read value matches the written value */
    if (read_value == test_value) {
        printf("PSG routines test PASSED: Written and read values match.\n");
    } else {
        printf("PSG routines test FAILED: Written value %d, but read value %d.\n", test_value, read_value);
    }
}
 
/*
 * Function: test_tone
 * Purpose: Tests tone generation by starting with one tone and changing it after user input.
 */
void test_tone() {
    printf("Testing tone generation on Channel A...\n");


    set_tone(0, 478);      
    set_volume(0, 10);         
    enable_channel(0, 1, 0);   

    printf("Playing tone (478). Press any key to change the tone.\n");

    while (!Cconis()) {
        Vsync(); 
    }

    Cnecin(); 
    set_tone(0, 319);          
    set_volume(0, 10);       
    enable_channel(0, 1, 0);  

    printf("Playing new tone (319). Press any key to stop.\n");

    while (!Cconis()) {
        Vsync(); 
    }
    Cnecin(); 

    set_volume(0, 0);
}

/*
 * Function: test_volume
 * Purpose: Tests volume control by playing a note, increasing the volume after a key press,
 *          and decreasing the volume after another key press.
 */
void test_volume() {
    printf("Testing volume control on Channel A...\n");

    set_tone(0, 478);        
    set_volume(0, 7);         
    enable_channel(0, 1, 0);  

    printf("Playing tone with initial volume (7). Press any key to increase volume.\n");

    while (!Cconis()) {
        Vsync();
    }
    Cnecin(); 

    set_volume(0, 15);      
    printf("Increased volume to maximum (15). Press any key to decrease volume.\n");

    while (!Cconis()) {
        Vsync(); 
    }
    Cnecin();

    set_volume(0, 3);         
    printf("Decreased volume to low (3). Press any key to stop.\n");

    while (!Cconis()) {
        Vsync();
    }
    Cnecin(); 

    set_volume(0, 0);
    printf("Volume test complete.\n");
}

/*
 * Function: test_enable_channel
 * Purpose: Tests enabling and disabling tone and noise on Channel A using key presses.
 */
void test_enable_channel() {
    printf("Testing enable_channel on Channel A...\n");

    set_tone(0, 478);       
    set_volume(0, 10);        
    enable_channel(0, 1, 0);  
    printf("Tone enabled on Channel A. Press any key to enable noise.\n");

    while (!Cconis()) {
        Vsync();
    }
    Cnecin(); 

    set_tone(0, 478);         
    set_volume(0, 10);        
    enable_channel(0, 1, 1);   
    printf("Noise enabled on Channel A. Press any key to disable tone.\n");

    while (!Cconis()) {
        Vsync(); 
    }
    Cnecin(); 

    set_volume(0, 10);         
    enable_channel(0, 0, 1);  
    printf("Tone disabled, noise still enabled on Channel A. Press any key to stop.\n");

    while (!Cconis()) {
        Vsync();
    }
    Cnecin(); 

    set_volume(0, 0);
    printf("Channel test complete.\n");
}

/*
 * Function: test_stop
 * Purpose: Tests the stop_sound function by playing a tone and stopping it on user input.
 */
void test_stop() {
    printf("Testing stop_sound function...\n");

    set_tone(0, 478);         
    set_volume(0, 10);         
    enable_channel(0, 1, 0);  
    printf("Tone is playing on Channel A. Press any key to stop the sound.\n");

    while (!Cconis()) {
        Vsync(); 
    }
    Cnecin(); 

    stop_sound();
    printf("All sound stopped. Test complete.\n");
} 

/*
 * Function: test_noise
 * Purpose: Tests the noise generator by enabling noise on Channel C
 *          and modifying it based on user input.
 */
void test_noise() {
    printf("Testing noise generator on Channel C...\n");

    set_noise(12);          
    set_volume(2, 10);         
    enable_channel(2, 0, 1);  
    printf("Noise enabled on Channel C with tuning 12. Press any key to change tuning.\n");

    while (!Cconis()) {
        Vsync(); 
    }
    Cnecin();

    set_noise(4);            
    set_volume(2, 10);       
    enable_channel(2, 0, 1);  
    printf("Noise tuning changed to 4. Press any key to stop.\n");

    while (!Cconis()) {
        Vsync(); 
    }
    Cnecin(); 

    set_volume(2, 0);
    printf("Noise test complete.\n");
}

/*
 * Function: test_envelope
 * Purpose: Tests the PSG envelope generator by cycling through
 *          different envelope shapes with user input.
 */
void test_envelope() {
    int shape;
    
    printf("Testing envelope generator on Channel A...\n");
    set_tone(0, 284);         
    set_volume(0, 8);        
    enable_channel(0, 1, 0);  
    printf("Tone enabled on Channel A. Press any key to cycle through envelope shapes.\n");

    for (shape = 0; shape < 16; shape++) {
        while (!Cconis()) {
            Vsync(); 
        }
        Cnecin();

        set_envelope(shape, 5000); 
    }
    set_volume(0, 0);
    printf("Envelope test finished.\n");
}

/*
 * Function: test_music
 * Purpose: Tests the music module by playing the predefined melody.
 */
void test_music() {

    UINT32 time_elapsed_melody = 0; 
    printf("Testing music module...\n");

    start_music();
    printf("Music started. Press any key to stop.\n");

    while (!Cconis()) {
        Vsync(); 
        update_music(&time_elapsed_melody); 
    }
    Cnecin();

    stop_sound();
    printf("Music test complete.\n");
} 

/*
 * Function: test_effects
 * Purpose: Tests sound effects by playing each effect sequentially.
 */
void test_effects() {
    printf("Testing sound effects...\n");


    printf("Playing point sound. Press any key to continue.\n");
    play_score();


    while (!Cconis()) {
        Vsync(); 
    }
    Cnecin(); 

    printf("Playing splat sound. Press any key to finish.\n");
    play_splat();

    while (!Cconis()) {
        Vsync();
    }
    Cnecin(); 

    printf("Sound effects test complete.\n");
}

