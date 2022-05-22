#include <detpic32.h>


//TIMER 3: TEMPO A 0 = 40ms e TEMPO a 1 = 40ms
//TIMER 1: TEMPO A 0 = 200ms e TEMPO a 1 = 200ms

int main(void)
{

    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD2 = 0;

    T3CONbits.TCKPS = 4;
    T1CONbits.TCKPS = 2;

    PR3 = 49999;
    PR1 = 63491;

    TMR3 = 0;
    TMR1 = 0;

    
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;



    EnableInterrupts();
    T3CONbits.TON = 1;
    T1CONbits.TON = 1;
    while(1)
    {

    }
}

void _int_(12) isr_T3(void)
{
    LATDbits.LATD2 = !LATDbits.LATD2;
    IFS0bits.T3IF = 0;
}

void _int_(4) isr_T1(void)
{

    LATDbits.LATD0 = !LATDbits.LATD0;
    IFS0bits.T1IF = 0;
}
