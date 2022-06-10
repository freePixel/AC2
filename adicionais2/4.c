#include <detpic32.h>


#define TRUE 1
#define FALSE 0
volatile int dutyCycle = 0;

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






void setPWM(int percentage)
{
    dutyCycle = percentage;
    OC3RS = (int)(19999 * (float)percentage / 100);
    OC5RS = (int)(19999 * (float)(100-percentage) / 100);
}

void _int_(27) isr_adc()
{
    int* ptr = (int*)(&ADC1BUF0);
            
    int i , s = 0;
    for(i=0;i<4;i++)
    s+= *(ptr + i*4);
    s /= 4;
    setPWM((int)(100.f * ((float)s / 1023)));
    IFS1bits.AD1IF = 0;

    IFS1bits.AD1IF = 0;
}

void _int_(20) isr_T5()
{
    if(dutyCycle == 100)
    {
        send2displays(toBcd(0) , TRUE);
        LATCbits.LATC14 = 1;
    }
    else{
        send2displays(toBcd(dutyCycle) , TRUE);
        LATCbits.LATC14 = 0;
    }
    IFS0bits.T5IF = 0;
}



void initialize()
{
    //initialize display
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISB &= 0xffff80ff;


    //TIMER 2 CONFIGURATION (USED TO GENERATE 1KHZ PWM SIGNAL)
    T2CONbits.TCKPS = 0;
    PR2 = 19999;
    TMR2 = 0;
    T2CONbits.TON = 1;

    //TIMER 5 CONFIGURATION
    T5CONbits.TCKPS = 2;
    PR5 = 49999;
    TMR5 = 0;
    T5CONbits.TON = 1;

    IPC5bits.T5IP = 2;
    IEC0bits.T5IE = 1;
    IFS0bits.T5IF = 0;


    //PWM CONFIGURATION
    OC3CONbits.OCM = 6;
    OC3CONbits.OCTSEL =0;
    OC3RS = 0;
    OC3CONbits.ON = 1;

    //3b
    OC5CONbits.OCM = 6;
    OC5CONbits.OCTSEL = 0;
    OC5RS = 0;
    OC5CONbits.ON = 1;

    //ADC CONFIGURATION
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 3;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    IPC6bits.AD1IP = 2;
    IEC1bits.AD1IE = 1;
    IFS1bits.AD1IF = 0;

    //RC14 CONFIGURATION
    TRISCbits.TRISC14 = 0;
    LATCbits.LATC14 = 0;



    EnableInterrupts();
}



int main(void)
{
    
    initialize();
    while(1)
    {
        if(readCoreTimer() >= 20000 * 100)
        {
            resetCoreTimer();
            AD1CON1bits.ASAM = 1;
        }
    }
}

