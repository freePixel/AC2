#define __LANGUAGE_C__
#include <detpic32.h> 

int main(void)
{
    //0111 1111 0000 0000
    TRISB = (TRISB & 0xffff80ff) | 0x00007f00;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    char s = 'a';
    while(1)
    {
        char s = getChar();

        LATB = LATB & 0x80ff;
        switch(s)
        {
            case 'a': LATBbits.LATB8 = 1; break;
            case 'b': LATBbits.LATB9 = 1; break;
            case 'c': LATBbits.LATB10 = 1; break;
            case 'd': LATBbits.LATB11 = 1; break;
            case 'e': LATBbits.LATB12 = 1; break;
            case 'f': LATBbits.LATB13 = 1; break;
            case 'g': LATBbits.LATB14 = 1; break;
        }
    }

    return 0;


}