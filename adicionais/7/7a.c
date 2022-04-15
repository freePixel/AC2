#include <detpic32.h>


int main(void)
{
    TRISB |= 0x000f;

    while(1)
    {
        printStr("DS4=");
        putChar(48 + PORTBbits.RB3);
        printStr(", ");

        printStr("DS3=");
        putChar(48 + PORTBbits.RB2);
        printStr(", ");

        printStr("DS2=");
        putChar(48 + PORTBbits.RB1);
        printStr(", ");

        printStr("DS1=");
        putChar(48 + PORTBbits.RB0);

        putChar('\n');

        resetCoreTimer();
        while(readCoreTimer() < 20000000);
    }
}

