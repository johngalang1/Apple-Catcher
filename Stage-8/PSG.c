#include "PSG.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: PSG.c
PURPOSE: CONTAINS FUNCTIONS FOR PSG MODULE
*/

volatile char *PSG_reg_select = (volatile char *)0xFF8800;
volatile char *PSG_reg_write = (volatile char *)0xFF8802;

/*
NAME: write_psg
PARAMETERS: 
    - reg: The register number to write to
    - value: The value to write to the specified register
PURPOSE: To safely write a value to a specified PSG register.
DETAILS: 
    - Switches to supervisor mode to gain access to the hardware registers.
    - Selects the target PSG register using the `PSG_reg_select` pointer.
    - Writes the provided value to the selected register using the `PSG_reg_write` pointer.
    - Restores to the previous mode after the operation to maintain system stability.
*/

void write_psg(int reg, UINT8 value)
{
    UINT32 old_ssp = Super(0); 

    *PSG_reg_select = reg;     
    *PSG_reg_write = value;    

    Super(old_ssp);            

    return;
}

/*
NAME: read_psg
PARAMETERS: 
    - reg: The register number to read from
PURPOSE: To safely read the current value from a specified PSG register.
DETAILS: 
    - Switches to supervisor mode to gain access to the hardware registers.
    - Selects the target PSG register using the `PSG_reg_select` pointer.
    - Reads the value from the selected register using the `PSG_reg_write` pointer.
    - Restores to the previous mode after the operation to maintain system stability.
    - Returns the value read from the specified PSG register.
*/

UINT8 read_psg(int reg)
{
    UINT32 old_ssp = Super(0);
    UINT8 value;

    *PSG_reg_select = reg;     
    value = *PSG_reg_select;    

    Super(old_ssp);          

    return value;             
}

 /*
NAME: set_tone
PARAMETERS: 
    - channel: The channel number to set the tone for.
    - tuning: The 12-bit tuning value that determines the frequency of the tone.
PURPOSE: To configure the tone frequency for a specified PSG channel.
DETAILS: 
    - Validates the input parameters to ensure the channel is within range (0–2) and the tuning value is within 12 bits.
    - Calculates the fine and coarse tuning registers for the specified channel.
    - Splits the 12-bit tuning value into two parts:
        - Fine tuning (lower 8 bits) is written to the fine tune register.
        - Coarse tuning (upper 4 bits) is written to the coarse tune register.
*/

void set_tone(int channel, int tuning)
{
    int fine_tune_reg, coarse_tune_reg;
    /* Check for valid Inputs */
    if (channel < 0 || channel > 2 || tuning < 0 || tuning > 0xFFF) {
        return; 
    }
    /* Fine tune: 0 for A, 2 for B, 4 for C */
    fine_tune_reg = channel * 2;     
    /* Coarse tune: next register */
    coarse_tune_reg = fine_tune_reg + 1; 

    /* Write the fine tune (lower 8 bits of tuning) */
    write_psg(fine_tune_reg, (UINT8)(tuning & 0xFF));

    /* Write the coarse tune (upper 4 bits of tuning) */
    write_psg(coarse_tune_reg, (UINT8)((tuning >> 8) & 0xF));
}

/*
NAME: set_volume
PARAMETERS: 
    - channel: The channel number to set the volume for.
    - volume: The volume level to set.
PURPOSE: To configure the volume level for a specified PSG channel.
DETAILS: 
    - Validates the input parameters to ensure the channel is within range (0–2) and the volume level is within 4 bits (0–15).
    - Calculates the volume register for the specified channel
    - Uses `write_psg` to safely write the volume value to the corresponding PSG register.
    - Only the lower 4 bits of the volume value are used, as PSG volume registers are 4 bits wide.
*/

void set_volume(int channel, int volume)
{
    int volume_reg;
    if (channel < 0 || channel > 2 || volume < 0 || volume > 15) {
        return; 
    }
    volume_reg = 8 + channel; 

    /* Write the volume to the appropriate register */
    write_psg(volume_reg, (UINT8)(volume & 0xF)); 
}
/*
NAME: enable_channel
PARAMETERS: 
    - channel: The channel number to configure.
    - tone_on: 1 to enable tone, 0 to disable tone for the specified channel.
    - noise_on: 1 to enable noise, 0 to disable noise for the specified channel.
PURPOSE: To enable or disable tone and noise generation for a specific PSG (Programmable Sound Generator) channel.
DETAILS: 
    - Validates the input parameters to ensure the channel is within range (0–2) and that tone_on and noise_on are boolean values (0 or 1).
    - Calculates bit masks for the tone and noise settings based on the channel:
        - Tone bits: 0, 1, or 2 in the mixer register for Channels A, B, or C.
        - Noise bits: 3, 4, or 5 in the mixer register for Channels A, B, or C.
    - Reads the current value of the mixer register (Register 7) to preserve settings for other channels.
    - Updates the mixer register value:
        - Clears the respective bit to enable tone or noise.
        - Sets the respective bit to disable tone or noise.
    - Writes the updated mixer value back to the mixer register using `write_psg`.
*/

void enable_channel(int channel, int tone_on, int noise_on)
{
    UINT8 mixer_value, tone_mask, noise_mask;

    if (channel < 0 || channel > 2 || (tone_on != 0 && tone_on != 1) || (noise_on != 0 && noise_on != 1)) {
        return; 
    }

    /* Tone bit (0, 1, or 2 for channels A, B, C) */
    tone_mask = 1 << channel;  
    /* Noise bit (3, 4, or 5 for channels A, B, C) */ 
    noise_mask = 1 << (channel + 3); 
    /* Register 7 is the mixer register */
    mixer_value = read_psg(7); 
    
    /* Update tone setting */
    if (tone_on) {
        mixer_value &= ~tone_mask; /* Enable tone by clearing the bit */
    } else {
        mixer_value |= tone_mask; /* Disable tone by setting the bit */
    }

    /* Update noise setting */
    if (noise_on) {
        mixer_value &= ~noise_mask; /* Enable noise by clearing the bit */
    } else {
        mixer_value |= noise_mask; /* Disable noise by setting the bit */
    }

    write_psg(7, mixer_value);
}
/*
NAME: stop_sound
PARAMETERS: None
PURPOSE: To immediately silence all sound production from the PSG.
DETAILS: 
    - Disables all tone and noise generation by setting all bits in the mixer register.
        - Writing `0x3F` to the mixer register ensures that tones and noises are disabled for Channels A, B, and C.
    - Mutes all channels by setting their volume registers (Registers 8, 9, and 10) to 0.
*/

void stop_sound()
{
    write_psg(7, 0x3F); 
    write_psg(8, 0);  
    write_psg(9, 0); 
    write_psg(10, 0); 
}
/*
NAME: set_noise
PARAMETERS: 
    - tuning: The noise tuning value (0–31).
PURPOSE: To configure the tuning of the noise generator in the PSG.
DETAILS: 
    - Validates the input to ensure the tuning value is within the 5-bit range (0–31).
    - Writes the validated tuning value to Register 6, which controls the frequency of the noise generator.
        - Only the lower 5 bits of the tuning value are used.
    - Lower tuning values produce faster, higher-pitched noise, while higher tuning values generate slower, lower-pitched noise.
    - This function does not enable or disable noise generation; it only sets the tuning value.
*/
void set_noise(int tuning)
{

    if (tuning < 0 || tuning > 31) {
        return; 
    }
    write_psg(6, (UINT8)(tuning & 0x1F)); 
}

/*
NAME: set_envelope
PARAMETERS: 
    - shape: The envelope shape (0–15).
    - sustain: The 16-bit sustain duration.
PURPOSE: To configure the envelope generator in the PSG with a specified shape and duration.
DETAILS: 
    - Validates the input parameters to ensure the envelope shape is within the 4-bit range (0–15) and the sustain duration does not exceed 16 bits.
    - Writes the envelope shape to Register 13, which determines the volume modulation pattern.
    - Splits the 16-bit sustain duration into two 8-bit values:
        - Lower 8 bits are written to Register 11.
        - Upper 8 bits are written to Register 12.
*/
void set_envelope(int shape, unsigned int sustain)
{
    UINT8 sustain_low, sustain_high;
    if (shape < 0 || shape > 15 || sustain > 0xFFFF) {
        return; 
    }
    /* Write the envelope shape to register 13 */
    write_psg(13, (UINT8)(shape & 0xF)); 

    /* Split the 16-bit sustain duration into two 8-bit parts */
    sustain_low = (UINT8)(sustain & 0xFF);       /* Lower 8 bits */
    sustain_high = (UINT8)((sustain >> 8) & 0xFF); /* Upper 8 bits */

    /* Write the sustain duration to registers 11 and 12 */
    write_psg(11, sustain_low);  /* Register 11: Lower byte */
    write_psg(12, sustain_high); /* Register 12: Upper byte */
}

