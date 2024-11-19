#include <osbind.h>
typedef unsigned char UINT8;
typedef UINT8 SCANCODE; 
volatile UINT8 * const IKBD_control = 0xFFFC00;
volatile const UINT8 * const IKBD_status = 0xFFFC00;
volatile const SCANCODE * const IKBD_RDR = 0xFFFC02; 
#define DISABLE_RECEIVE 0x16; 
#define ENABLE_RECEIVE 0x96; 
#define RDR_FULL ((UINT8)0x01) 
#define ESC_MAKE ((SCANCODE)0x01)
#define ESC_BREAK ((SCANCODE)0x81)

SCANCODE read_scancode();
char *scancode_2_ascii;
char ch;

int main()
{
    SCANCODE scancode;
    long orig_ssp = Super(0);
    *IKBD_control = DISABLE_RECEIVE;  
    
    scancode = read_scancode();
    scancode_2_ascii = (char *)((Keytbl(-1, -1, -1))->unshift);

    while (read_scancode() != ESC_MAKE)
    {   
        ch = scancode_2_ascii[scancode]; 
        Cconout(ch); 
        scancode = read_scancode();
    } 

    while (read_scancode() != ESC_BREAK);

    *IKBD_control = ENABLE_RECEIVE; 
    Super(orig_ssp);
    return 0;
}



SCANCODE read_scancode()
{
while (!(*IKBD_status & RDR_FULL))
;
return *IKBD_RDR;
}
