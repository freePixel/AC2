#include <detpic32.h>


int main(void)
{
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;

    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;

    while(1)
    {
        LATEbits.LATE0 = PORTBbits.RB0;
        LATEbits.LATE1 = PORTBbits.RB1;
        LATEbits.LATE2 = PORTBbits.RB2;
        LATEbits.LATE3 = PORTBbits.RB3;
    }

    return 0;
}