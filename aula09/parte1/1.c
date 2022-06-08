#include <detpic32.h>

#define TRUE 1
#define FALSE 0

volatile int volts = 0;

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



void initialize()
{

    TRISB = TRISB & 0xffff80ff;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISBbits.TRISB0 = 1;
    EnableInterrupts();
}


int main(void)
{


    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 3;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;
    int arr[4];
    int i = 0 , j = 0;
    int volts = 0;
    while(1)
    {
        if(i == 0)
        {
            AD1CON1bits.ASAM = 1;
            while(IFS1bits.AD1IF == 0);

            int* p = (int*)(&ADC1BUF0);
            for(j=0;j<4;j++)
            {
                arr[j] = (p[j*4]*33+511)/1023;
            }
            volts = (arr[0]+arr[1]+arr[2]+arr[3]) / 4;

            IFS1bits.AD1IF = 0;
        }

        send2displays(toBcd(volts) , TRUE);
        delay(10);
        i = (i+1) % 20;
    }

    return 0;
}