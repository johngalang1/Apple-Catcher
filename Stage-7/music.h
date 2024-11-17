#ifndef MUSIC_H
#define MUSIC_H

#include "PSG.h"
#include "types.h" 

/* 
AUTHORS: John G, Zach L
FILE NAME: effects.h
PURPOSE: CONTAINS FUNCTIONS PROTOTYPES FOR MUSIC MODULE
*/

void start_music();
void update_music(UINT32 *time_elapsed_melody);

#endif