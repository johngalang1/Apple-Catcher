#ifndef PSG_H
#define PSG_H
#include "types.h"
#include <osbind.h> 

/* 
AUTHORS: John G, Zach L
FILE NAME: PSG.h
PURPOSE: CONTAINS FUNCTION PROTOTYPES FOR PSG MODULE
*/

extern volatile char *PSG_reg_select;
extern volatile char *PSG_reg_write;

void write_psg(int reg, UINT8 val);

UINT8 read_psg(int reg);

void set_tone(int channel, int tuning);

void set_volume(int channel, int volume);

void enable_channel(int channel, int tone_on, int noise_on);

void stop_sound();

void set_noise(int tuning);

void set_envelope(int shape, unsigned int sustain);

#endif