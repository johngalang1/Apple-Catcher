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
PURPOSE: CONTAINS FUNCTION PROTOTYPES FOR TESTING RENDERING
*/

void test_basket_render(UINT32 *base32, UINT16 *base16, basket *b);

void test_apple_render(UINT32 *base32, UINT16 *base16, apple *a, basket *b);

void test_score_render(UINT32 *base32, UINT16 *base16, apple *a, basket *b,
                        score *score);

void test_frame_render(UINT32 *base32, UINT16 *base16, model *curr_model);

void test_master_render(UINT32 *base32, UINT16 *base16, apple *a, basket *b,
                        score *score, timer_round *rt, timer_start *st);

#endif