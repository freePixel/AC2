#include <detpic32.h>


volatile  unsigned char voltage = 0;

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

void _int_(27) isr_adc(void)
{
    int* p = (int*)(&ADC1BUF0);
    int total = 0;
    int i;
    for(i=0;i<8;i++)
    {
        total += p[i*4];
    }

    int average = total / 8;
    voltage = (average*33+511)/1023;

    IFS1bits.AD1IF = 0;
    
}


int main(void)
{
    unsigned int cnt = 0;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    TRISB = TRISB & 0x80ff;

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 7;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    while(1)
    {
        if(cnt == 0)
        {
            AD1CON1bits.ASAM = 1;
        }

        send2displays(toBcd(voltage) , TRUE);
        cnt = (cnt + 1) % 20;
        delay(10);
    }

    return 0;
}

