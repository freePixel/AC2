#include <detpic32.h>


static const char display7Scodes[] = {

    (char)0x3f ,
    (char)0x06 ,
    (char)0x5b ,
    (char)0x4f ,
    (char)0x66 ,
    (char)0x6d ,
    (char)0x7d ,
    (char)0x07 ,
    (char)0x7f ,
    (char)0x6f ,
    (char)0x77 ,
    (char)0x7c ,
    (char)0x39 ,
    (char)0x5e ,
    (char)0x79 ,
    (char)0x71

};

int main(void)
{
    TRISB = (TRISB & 0xffff80ff) | 0x0000000f;
    
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5   = 0;
    LATDbits.LATD6   = 1;

    while(1)
    {
        int counter = (PORTB & 0x0000000f);
        char seg = display7Scodes[counter];

        LATB = (LATB & 0xffff80ff) | (seg << 8);
    }

    return 0;

}