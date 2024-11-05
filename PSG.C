#include <osbind.h>

int main()
{
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write  = 0xFF8802;

    long old_ssp = Super(0);

    // Set up Channel A for note C (261 Hz)
    *PSG_reg_select = 0;        /* set channel A fine tune */
    *PSG_reg_write  = 230;      /* tone period for C */
    *PSG_reg_select = 1;        /* set channel A coarse tune */
    *PSG_reg_write  = 0;

    // Set up Channel B for note E (329 Hz)
    *PSG_reg_select = 2;        /* set channel B fine tune */
    *PSG_reg_write  = 194;      /* tone period for E */
    *PSG_reg_select = 3;        /* set channel B coarse tune */
    *PSG_reg_write  = 0;

    // Set up Channel C for note G (392 Hz)
    *PSG_reg_select = 4;        /* set channel C fine tune */
    *PSG_reg_write  = 164;      /* tone period for G */
    *PSG_reg_select = 5;        /* set channel C coarse tune */
    *PSG_reg_write  = 0;

    // Enable Channels A, B, C on the mixer
    *PSG_reg_select = 7;
    *PSG_reg_write  = 0x38;     /* Enable A, B, C */

    // Set volume for Channel A (C note)
    *PSG_reg_select = 8;
    *PSG_reg_write  = 11;

    // Set volume for Channel B (E note)
    *PSG_reg_select = 9;
    *PSG_reg_write  = 11;

    // Set volume for Channel C (G note)
    *PSG_reg_select = 10;
    *PSG_reg_write  = 11;

    while (!Cconis())           /* Chord now playing, await key */
        ;

    // Turn off sound for all channels
    *PSG_reg_select = 8;
    *PSG_reg_write  = 0;

    *PSG_reg_select = 9;
    *PSG_reg_write  = 0;

    *PSG_reg_select = 10;
    *PSG_reg_write  = 0;

    Cnecin();

    /* Super(old_ssp); */
    return 0;
}
