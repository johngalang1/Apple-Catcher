#ifndef DRIVER_H
#define DRIVER_H
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h"
#include "types.h"
#include <stdio.h>
#include <osbind.h>
#include "renderer.h" 
#include "input.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: driver.h
PURPOSE: CONTAINS FUNCTION PROTOTYPE FOR RENDERING SCREEN
*/

void render_model(UINT32 *base32, UINT16 *base16, apple *a, basket *b,
                        score *score, timer_round *rt, timer_start *st); 

#endif