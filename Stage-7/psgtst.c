#include <osbind.h>
#include <stdio.h>
#include "music.h"
#include "PSG.h"
#include "effects.h"
#include "driver.h"
/* 
AUTHORS: John G, Zach L
FILE NAME: psgtst.c
PURPOSE: CONTAINS TESTING FOR STAGE 7
*/

void display_menu() {
    printf("Select a test to run:\n");
    printf("1 - Test PSG Routines\n");
    printf("2 - Test Tone Generation\n");
    printf("3 - Test Volume Control\n");
    printf("4 - Test Channel Configuration\n");
    printf("5 - Test Stop Sound\n");
    printf("6 - Test Noise Generator\n");
    printf("7 - Test Envelope Generator\n");
    printf("8 - Test Music Module\n");
    printf("9 - Test Sound Effects\n");
    printf("Q - Quit\n");
}

int main() {
    char choice;
    display_menu();

    while (1) {
        printf("\nEnter your choice: ");
        choice = Cnecin(); 

        switch (choice) {
            case '1':
                test_psg_routines();
                break;
            case '2':
                test_tone();
                break;
            case '3':
                test_volume();
                break;
            case '4':
                test_enable_channel();
                break;
            case '5':
                test_stop();
                break;
            case '6':
                test_noise();
                break;
            case '7':
                test_envelope();
                break;
            case '8':
                test_music();
                break;
            case '9':
                test_effects();
                break;
            case 'Q':
            case 'q':
                return 0; 
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
        display_menu();
    }

    return 0;
}