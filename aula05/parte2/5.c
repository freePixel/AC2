#include <detpic32.h>

#define TRUE 1
#define FALSE 0

#define UP 2
#define DOWN 3
#define HALT_UP 4
#define HALT_DOWN 5

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
    TRISBbits.TRISB0 = 1;
    int counter = 0, i = 0 , j=0 , k=0;
    int STATE = UP;
    int FREQUENCY = 150;
    while(1)
    {
        if (PORTBbits.RB0 && counter < 59)
        {
            STATE = UP;
        }
        else if(!PORTBbits.RB0  && counter > 0){
            STATE = DOWN;
        }
        else if(PORTBbits.RB0){
            STATE = HALT_UP;
        }
        else{
            STATE = HALT_DOWN;
        }
        

        if(STATE == UP)
        {
            counter = (counter + 1) % 60;
            FREQUENCY = 20;
        }
        else if(STATE == DOWN){
            counter = (counter + 60 - 1) % 60;
            FREQUENCY = 50;
        }
        else if(STATE == HALT_UP)
        {
            for(j=0;j<11;j++)
            {
                for(k=0;k<20;k++)
                {
                    send2displays(toBcd(counter) , TRUE);
                    delay(10);
                }
                send2displays(0 , FALSE);
                delay(200);
            }
            delay(200);
        }
        else if(STATE == HALT_DOWN)
        {
            for(j=0;j<5;j++)
            {
                for(k=0;k<50;k++)
                {
                    send2displays(toBcd(counter) , TRUE);
                    delay(10);
                }
                send2displays(0,  FALSE);
                delay(500);
            }
        }
        
        i = 0;
        if(STATE == UP || STATE == DOWN)
        {
            do{
            send2displays(toBcd(counter) , TRUE);
            delay(10);
            }
            while(++i < FREQUENCY);
        }
    }

    return 0;
}