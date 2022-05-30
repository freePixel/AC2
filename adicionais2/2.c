#include <detpic32.h>

int counter = 0;






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

void _int_(4) isr_T1()
{
    counter++;
    if(counter >= 100) counter = 0;
    printInt(counter , 16 | (2 << 16));
    putChar('\n');
    IFS0bits.T1IF = 0;
}

void _int_(8) isr_T2()
{
    send2displays(toBcd(counter) , 1);
    IFS0bits.T2IF = 0;
}

void setFreq1(int freq)
{
    int k = (int)ceil(20000000 / (65536 * freq));
    if(k <= 1) T1CONbits.TCKPS  = 0;
    if(k <= 8) T1CONbits.TCKPS  = 1;
    if(k <= 64) T1CONbits.TCKPS = 2;
    if(k <= 256) T1CONbits.TCKPS = 3;

    switch(T1CONbits.TCKPS)
    {
        case 0: PR1 = (20000000 / 1)   / (freq) - 1; break;
        case 1: PR1 = (20000000 / 8)   / (freq) - 1; break;
        case 2: PR1 = (20000000 / 64)  / (freq) - 1; break;
        case 3: PR1 = (20000000 / 256) / (freq) - 1; break;
    }
}



void initialize(void)
{
    //initialize display
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISB &= 0xffff80ff;

    //initialize timer 1
    T1CONbits.TCKPS = 2;
    PR1 = 31249;
    TMR1 = 0;
    T1CONbits.TON = 1;

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    //initialize timer 2
    T2CONbits.TCKPS = 3;
    PR2 = 49999;
    TMR2 = 0;
    T2CONbits.TON = 1;

    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    //initialize ADC
    

    EnableInterrupts();
}



int main(void)
{
    initialize();
    int freq = 0;
    while(1)
    {
        char s = inkey();
        if(s != '\0')
        {
            if(s >= '0' && s <= '4')
            {
                freq = 2 * (1 + (s - 48));
                
                setFreq1(freq);
            }
            else{
                printStr("Nova frequência: ");
                printInt10(freq/2 - 1);
                putChar('\n');
            }
        }
    }
}