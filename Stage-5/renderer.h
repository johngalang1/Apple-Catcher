#ifndef RENDERER_H
#define RENDERER_H
#include "types.h"
#include "bitmaps.h"
#include "model.h"
#include "RASTER.H"
#include <osbind.h>

/* 
AUTHORS: John G, Zach L
FILE NAME: renderer.h
PURPOSE: CONTAINS FUNCTION PROTOTYPES FOR RENDERING IMAGES ON THE SCREEN
*/


void render_apple(UINT32 *base, apple *a, int op);

void render_basket(UINT32 *base, basket *b, int op);

void render_score(UINT16 *base, score *score);

void render_round_timer(UINT16 *base, timer_round *rt);

void render_start_timer(UINT16 *base, timer_start *st);

void display_message(message *msg);

void clear_message(message *msg);

const UINT16 *get_bitmap_for_char(char c);

void render_borders(UINT16 *base);


#endif
