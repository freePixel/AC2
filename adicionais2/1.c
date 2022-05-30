#include <detpic32.h>

#define  TRUE 1
#define  FALSE 0



unsigned char disp_value;
int disp_active = TRUE;

void delay(int ms)
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

void _int_(8) isr_T2(void)
{
    if(disp_value == 0xff) send2displays(0xff , disp_active);
    else{
        send2displays(toBcd(disp_value) , disp_active);
    }
    IFS0bits.T2IF = 0;

}

void initialize(void)
{
    TRISB = (TRISB & 0xffff80ff);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    T2CONbits.TCKPS = 2;
    PR2 = 49999;
    TMR2 = 0;
    T2CONbits.TON = 1;

    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    EnableInterrupts();

    TRISE = (TRISE & 0xfffffff0);
}


int main(void)
{

    initialize();

    disp_active = FALSE;
    LATE = (LATE & 0xfffffff0);

    while(1)
    {
        char s = inkey();
        
        if(s == 0) continue;
        switch(s)
        {
            case '0':
            disp_value = 0;
            LATE = (LATE & 0xfffffff0) | (0x1);
            disp_active = TRUE;
            break;
            
            case '1':
            disp_value = 1;
            LATE = (LATE & 0xfffffff0) | (0x2);
            disp_active = TRUE;
            break;

            case '2':
            disp_value = 2;
            LATE = (LATE & 0xfffffff0) | (0x4);
            disp_active = TRUE;
            break;

            case '3':
            disp_value = 3;
            LATE = (LATE & 0xfffffff0) | (0x8);
            disp_active = TRUE;
            break;

            default:
            disp_active = TRUE;
            disp_value = 0xff;
            LATE = (LATE & 0xfffffff0) | (0xf);
            delay(1000);
            disp_active = FALSE;
            LATE = (LATE & 0xfffffff0);
            break;
        }
    }
}