#include <detpic32.h>

#define TRUE 1
#define FALSE 0

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

void send2displays(unsigned char value , int active)
{
    static const char display7Scodes[] = {0x3f , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d , 0x7d , 0x07 , 0x7f , 0x6f , 0x77 , 0x7c , 0x39 , 0x5e , 0x79 , 0x71};
    static char displayFlag = 0;
    
    unsigned char digit_low;
    unsigned char digit_high;

    if(active)
    {
        digit_low = value & 0x0f;
        digit_high = value >> 4;

        if(displayFlag)
        {
            LATB = (LATB & 0xffff80ff) | (display7Scodes[digit_low] << 8);
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
        }
        else{
            LATB = (LATB & 0xffff80ff) | (display7Scodes[digit_high] << 8);
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
        }

        displayFlag = !displayFlag;
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 0;
    }
}

int main(void)
{
    TRISB = TRISB & 0xffff80ff;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    int counter = 0, i = 0;
    while(1)
    {
        i = 0;
        do{
            send2displays(counter , TRUE);
            delay(10);
        }
        while(++i < 20);

        counter = (counter + 1) % 256;
    }

    return 0;
}