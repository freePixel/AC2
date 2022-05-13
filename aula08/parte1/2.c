#include <detpic32.h>

int main(void)
{
    T3CONbits.TCKPS = 5;
    PR2 = 312499;
    TMR3 = 0;
    
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T2IF = 0;
    EnableInterrupts();
    T3CONbits.TON = 1;
    while(1)
    {

    }
    return 0;
}

void _int_(12) isr_T3(void)
{
    putChar('.');
    IFS0bits.T3IF = 0;
}

