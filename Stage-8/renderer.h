
#ifndef RENDERER_H
#define RENDERER_H
#include "types.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "input.h"
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

void display_message(const message *msg, UINT16 *buffer);

void clear_message(message *msg,  UINT16 *buffer);

const UINT16 *get_bitmap_for_char(char c);

void render_borders(UINT16 *base);

void update_model(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt); 

void render_message(UINT16 *buffer); 

void render_pregame(UINT32 *front_buffer, UINT32 *back_buffer, model *curr_model);

#endif
