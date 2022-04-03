#include <detpic32.h>


#define K 20000

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < K * ms);
} 

void send2displays(unsigned char value)
{
    static const char display7Scodes[] = {0x3f, 0x06 , 0x5b , 0x4f , 0x66 , 0x6d , 0x7d , 0x07 , 0x7f , 0x6f , 0x77 , 0x7c , 0x39 , 0x5e , 0x79 , 0x71};
    unsigned char d1 = display7Scodes[value >> 4];
    unsigned char d2 = display7Scodes[value & 0x0f];

    

    LATDbits.LATD6 = 1;
    LATB = (LATB & 0xffff80ff) | (d1 << 8);
    LATDbits.LATD6 = 0;

   //LATDbits.LATD5 = 0;
    //LATB = (LATB & 0xffff80ff) | (0x06 << 8);
    //LATDbits.LATD5 = 1;
}

int main(void)
{
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;

    TRISB = TRISB & 0xffff80ff;


    while(1)
    {
        send2displays(0x15);
        delay(1000);
    }
}