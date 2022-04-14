#include <detpic32.h>


#define TRUE 1
#define FALSE 0

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
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


    char s = '\0';
    char u = '\0';

    int i=0;

    int last = -1;
    while(1)
    {
        do{
            s = u;
            u = inkey();
        }
        while(u != '\0');

        switch(s)
        {
            case '0':
                send2displays(toBcd(0) , TRUE);
                last = 0;
                break;

            case '1':
                send2displays(toBcd(1) , TRUE);
                last = 1;
                break;

            case '2':
                send2displays(toBcd(2) , TRUE);
                last = 2;
                break;

            case '3':
                send2displays(toBcd(3) , TRUE);
                last = 3;
                break;

            case '\0':
            if(last != -1)
                send2displays(last , TRUE);
            else{
                send2displays(0 , FALSE);
            }
            break;

            default:
                for(i=0;i<100;i++)
                {
                    send2displays(0x0f , TRUE);
                    delay(10);
                }

                send2displays(-1 , FALSE);
                last = -1;
                break;
        }

        delay(10);
    }

    return 0;
}

