#include <osbind.h>
#include "time.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: time.c
PURPOSE: CONTAINS TIMER
*/

unsigned long get_time() {
    unsigned long *timer_address = (unsigned long *)0x462;
    unsigned long time;

    unsigned long old_sr = Super(0);  
    time = *timer_address;
    Super(old_sr);                    

    return time;
}
