#include <detpic32.h>

#define TRUE  1
#define FALSE 0
// baurate = 115200 bps

void putc(char byte)
{
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void putc1(char byte)
{
    while(U1STAbits.UTXBF == 1);
    U1TXREG = byte;
}

void initialize(void)
{
    //UART2 CONFIGURATION
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    //UART1 CONFIGURATION
    U1BRG = 10;
    U1MODEbits.BRGH = 0;
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    U1MODEbits.ON = 1;

    //TIMER CONFIGURATION
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    TRISDbits.TRISD3 = 0;
}

int main(void)
{
    initialize();

    while(TRUE)
    {
        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0;
        putc1((char)0xe4); // 0xA5, 0xF0, 0x0F, 0xFF , 0x00
        
        


    }

    return 0;

}