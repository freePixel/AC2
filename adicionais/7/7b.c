#include <detpic32.h>


int main(void)
{
    TRISB |= 0x000f;

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 1;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    while(1)
    {
        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);

        int* value = (int*)(&ADC1BUF0);

        IFS1bits.AD1IF = 0;
        

        int frequency = 1 +(*value)/(1023/4);
        
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
        while(readCoreTimer() < 20000000 / frequency);
    }

//1 -> 0
//x -> y
//5 -> 1023

}