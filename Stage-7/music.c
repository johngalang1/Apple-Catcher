#include "music.h"
#include "PSG.h" 

/* 
AUTHORS: John G, Zach L
FILE NAME: music.c
PURPOSE: CONTAINS FUNCTIONS FOR MUSIC MODULE
*/

typedef struct {
    int pitch;    /* Tone tuning value (12-bit value for PSG) */
    int duration; /* Duration of the note in vertical blank intervals (70 Hz ticks) */
} Note;

static Note melody[] = {
    {451 / 2, 26}, /* C# */ 
    {0, 2},  
    {268 / 2, 18}, /* A# */
    {0, 2},  
    {301 / 2, 26}, /* G# */ 
    {0, 2},  
    {268 / 2, 18}, /* A# */
    {0, 2},  
    {301 / 2, 26}, /* G# */ 
    {0, 2}, 

    {451 / 2, 26}, /* C# */ 
    {0, 2},  
    {268 / 2, 18}, /* A# */
    {0, 2},  
    {301 / 2, 26}, /* G# */ 
    {0, 2},  
    {268 / 2, 18}, /* A# */
    {0, 2},  
    {301 / 2, 26}, /* G# */ 
    {0, 2}, 

    {268 / 2, 16}, /* A# */
    {301 / 2, 16}, /* G# */
    {358 / 2, 24}, /* F */
    {0, 4},  
    {358 / 2, 28}, /* F */
    {402 / 2, 20}, /* D# */
    {358 / 2, 96}, /* F */

    /* //////// */

    {451 / 2, 26}, /* C# */ 
    {0, 2},  
    {268 / 2, 18}, /* A# */
    {0, 2},  
    {301 / 2, 26}, /* G# */ 
    {0, 2},  
    {268 / 2, 18}, /* A# */
    {0, 2},  
    {301 / 2, 26}, /* G# */ 
    {0, 2}, 

    {451 / 2, 26}, /* C# */ 
    {0, 2},  
    {268 / 2, 18}, /* A# */
    {0, 2},  
    {301 / 2, 26}, /* G# */ 
    {0, 2},  
    {268 / 2, 18}, /* A# */
    {0, 2},  
    {301 / 2, 26}, /* G# */ 
    {0, 2}, 

    {0, 2},   
    {301 / 2, 26}, /* G# */ 
    {0, 2},   
    {268 / 2, 26}, /* A# */ 
    {0, 2},   
    {253 / 2, 16}, /* B */ 
    {0, 2},   
    {268 / 2, 24}, /* A# */ 
    {0, 2},   
    {301 / 2, 18}, /* G# */ 
    {0, 2},   
    {358 / 2, 82}, /* F */ 
    {0, 2},   
};


static Note melody_b[] = {
    {451 * 2, 62},  /* C# - Base octave */
    {451, 62},      /* C# - One octave higher */

    {451 * 2, 62},  /* C# - Base octave */
    {451, 62},      /* C# - One octave higher */

    {358 * 2, 200}, /* F - Base octave */
    {0, 4},        

    {451 * 2, 62},  /* C# - Base octave */
    {451, 62},      /* C# - One octave higher */

    {451 * 2, 62},  /* C# - Base octave */
    {451, 62},      /* C# - One octave higher */

    {358 * 2, 100}, /* F - Base octave */  
    {0, 10},       
    {358 * 2, 45}, /* F - Base octave */   
    {0, 2},        
    {358 * 2, 45}, /* F - Base octave */  
    {0, 2},     
};



/* Number of notes in the melody */
#define MELODY_LENGTH (sizeof(melody) / sizeof(Note))
#define MELODY_B_LENGTH (sizeof(melody_b) / sizeof(Note)) 

static int current_note_index_b = 0;   /* Index of the current note for Channel B */
static int remaining_duration_b = 0;  /* Time left for the current note on Channel B */
 
/* Variables to keep track of the melody's state */
static int current_note_index = 0;    /* Index of the current note */
static int remaining_duration = 0;   /* Time left for the current note */

/*
NAME: start_music
PARAMETERS: None
PURPOSE: To initialize and start playing the predefined melody on the PSG.
DETAILS:
    - Resets the melody to the beginning by setting the `current_note_index` to 0.
    - Loads the duration of the first note into the `remaining_duration` variable.
    - If the first note has a non-zero pitch:
        - Configures the note's pitch using `set_tone`.
        - Sets the volume using `set_volume`.
        - Enables tone generation on Channel A using `enable_channel`.
    - If the first note is a rest (pitch = 0):
        - Mutes the Channel by setting its volume to 0.
*/
void start_music()
{
    /* Initialize Channel A */
    current_note_index = 0; 
    remaining_duration = melody[current_note_index].duration;

    if (melody[current_note_index].pitch > 0) {
        set_tone(0, melody[current_note_index].pitch); 
        set_volume(0, 10); 
        enable_channel(0, 1, 0); 
    } else {
        set_volume(0, 0);
    }

    /* Initialize Channel B */
    current_note_index_b = 0;
    remaining_duration_b = melody_b[current_note_index_b].duration;

    if (melody_b[current_note_index_b].pitch > 0) {
        set_tone(1, melody_b[current_note_index_b].pitch); 
        set_volume(1, 8); 
        enable_channel(1, 1, 0); 
    } else {
        set_volume(1, 0);
    }
}


/*
NAME: update_music
PARAMETERS: 
    - time_elapsed_melody: Pointer to a counter tracking the total elapsed time in vertical blank intervals (1/70th of a second).
PURPOSE: To update the melody playback by transitioning to the next note when the current note’s duration ends.
DETAILS:
    - Decrements the `remaining_duration` counter for the current note.
    - When `remaining_duration` reaches 0:
        - Advances `current_note_index` to the next note in the melody.
        - If the end of the melody is reached, wraps back to the first note.
        - Loads the duration of the new note into `remaining_duration`.
        - If the new note has a non-zero pitch:
            - Configures the note's pitch using `set_tone`.
            - Sets the volume by using `set_volume`.
            - Enables tone generation by using `enable_channel`.
        - If the new note is a rest (pitch = 0):
            - Mutes Channel A by setting its volume to 0.
    - Increments the `time_elapsed_melody` counter to keep track of total elapsed time during playback.
*/
void update_music(UINT32 *time_elapsed_melody)
{
    /* Update Channel A */
    if (--remaining_duration <= 0) {
        current_note_index = (current_note_index + 1) % MELODY_LENGTH;
        remaining_duration = melody[current_note_index].duration;

        if (melody[current_note_index].pitch > 0) {
            set_tone(0, melody[current_note_index].pitch); 
            set_volume(0, 10);
            enable_channel(0, 1, 0); 
        } else {
            set_volume(0, 0);
        }
    }

    /* Update Channel B */
    if (--remaining_duration_b <= 0) {
        current_note_index_b = (current_note_index_b + 1) % MELODY_B_LENGTH;
        remaining_duration_b = melody_b[current_note_index_b].duration;

        if (melody_b[current_note_index_b].pitch > 0) {
            set_tone(1, melody_b[current_note_index_b].pitch); 
            set_volume(1, 8);
            enable_channel(1, 1, 0); 
        } else {
            set_volume(1, 0);
        }
    }

    /* Increment the elapsed time counter */
    (*time_elapsed_melody)++;
}
