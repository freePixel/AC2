#include <detpic32.h>

volatile char tCount = 0;

int main(void)
{
    TRISDbits.TRISD8 = 1;
    TRISEbits.TRISE0 = 0;

    T1CONbits.TCKPS = 2;
    PR1 = 39062;
    TMR1 = 0;
    
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    INTCONbits.INT1EP = 0;
    IPC1bits.INT1IP = 2;
    IFS0bits.INT1IF = 0;
    IEC0bits.INT1IE = 1;
    

    EnableInterrupts();

    while(1)
    {

    }
    return 0;

}


void _int_(8) isr_T2(void)
{
    tCount++;
    if(tCount == 6)
    {
        LATEbits.LATE0 = 0;
        T1CONbits.TON = 0;
    }
    IFS0bits.T1IF = 0;

}

void _int_(7) isr_INT1(void)
{
    T1CONbits.TON = 1;
    IFS0bits.INT1IF = 0;
    LATEbits.LATE0 = 1;
    tCount = 0;
}