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
    {478, 35}, /* C, 0.5 seconds */
    {379, 35}, /* E, 0.5 seconds */
    {319, 35}, /* G, 0.5 seconds */
    {284, 35}, /* B, 0.5 second */
    {319, 35}, /* G, 0.5 seconds */
    {379, 35}, /* E, 0.5 seconds */
    {478, 35}, /* C, 0.5 seconds */ 
    {379, 35}, /* E, 0.5 seconds */
    {319, 35}, /* G, 0.5 seconds */
    {284, 35}, /* B, 0.5 second */
    {319, 35}, /* G, 0.5 seconds */
    {379, 35}, /* E, 0.5 seconds */
    {426, 35}, /* D, 0.5 seconds */
    {358, 35}, /* F, 0.5 seconds */
    {284, 35}, /* A, 0.5 seconds */
    {253, 35}, /* B, 0.5 seconds */
    {284, 35}, /* A, 0.5 seconds */
    {358, 35}, /* F, 0.5 seconds */
    {426, 35}, /* D, 0.5 seconds */
    {358, 35}, /* F, 0.5 seconds */
    {284, 35}, /* A, 0.5 seconds */
    {253, 35}, /* B, 0.5 seconds */
    {284, 35}, /* A, 0.5 seconds */
    {358, 35}, /* F, 0.5 seconds */
};

/* Number of notes in the melody */
#define MELODY_LENGTH (sizeof(melody) / sizeof(Note))
 
/* Variables to keep track of the melody's state */
static int current_note_index = 0;    /* Index of the current note */
static int remaining_duration = 0;   /* Time left for the current note */

/*
NAME: start_music
PARAMETERS: None
PURPOSE: To initialize and start playing the predefined melody on the PSG (Programmable Sound Generator).
DETAILS:
    - Resets the melody to the beginning by setting the `current_note_index` to 0.
    - Loads the duration of the first note into the `remaining_duration` variable.
    - If the first note has a non-zero pitch:
        - Configures Channel A with the note's pitch using `set_tone`.
        - Sets the volume of Channel A to medium using `set_volume`.
        - Enables tone generation on Channel A using `enable_channel`.
    - If the first note is a rest (pitch = 0):
        - Mutes Channel A by setting its volume to 0.
    - Prepares the PSG to start playback of the melody seamlessly.
*/
void start_music()
{
    current_note_index = 0; /* Reset melody to the beginning */
    remaining_duration = melody[current_note_index].duration;

    if (melody[current_note_index].pitch > 0) {
        set_tone(0, melody[current_note_index].pitch); 
        set_volume(0, 10); 
        enable_channel(0, 1, 0); 
    } else {
        set_volume(0, 0);
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
            - Configures Channel A with the note's pitch using `set_tone`.
            - Sets the volume of Channel A using `set_volume`.
            - Enables tone generation on Channel A using `enable_channel`.
        - If the new note is a rest (pitch = 0):
            - Mutes Channel A by setting its volume to 0.
    - Increments the `time_elapsed_melody` counter to keep track of total elapsed time during playback.
    - Ensures seamless playback of the melody, transitioning smoothly between notes without gaps.
*/
void update_music(UINT32 *time_elapsed_melody)
{
    /* Decrement the remaining duration for the current note */
    if (--remaining_duration <= 0) {
        /* Move to the next note in the melody */
        current_note_index = current_note_index + 1;
        if (current_note_index >= MELODY_LENGTH) {
            current_note_index = 0; /* Wrap back to the beginning of the melody */
        }
        remaining_duration = melody[current_note_index].duration;

        if (melody[current_note_index].pitch > 0) {
            set_tone(0, melody[current_note_index].pitch); 
            set_volume(0, 10);
            enable_channel(0, 1, 0); 
        } else {
            set_volume(0, 0);
        }
    }
    /* Increment the elapsed time counter */
    (*time_elapsed_melody)++;
}
