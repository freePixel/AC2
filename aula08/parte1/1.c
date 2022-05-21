#include <detpic32.h>


int main(void)
{
<<<<<<< HEAD
    T3CONbits.TCKPS = 7;
    PR3 = 39062;
=======
    T3CONbits.TCKPS = 5;
    PR3 = 312499;
>>>>>>> 9ddac1a627c02dac0e2260a7e110b8e4a5ee1fb3
    TMR3 = 0;
    T3CONbits.TON = 1;
    while(1)
    {
        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0;
        putChar('.');
    }
    return 0;
}

