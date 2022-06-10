#include <detpic32.h>


/*
    compile & run command: pcompile 5.c && ldpic32 5.hex && pterm 1200
*/

#define TRUE 1
#define FALSE 0

void sendByte(char byte)
{
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;

}

void sendStr(char* str)
{
    while(*str != '\0')
    {
        sendByte(*str);
        str++;
    }
}

void _int_(4) isr_t1()
{

    sendStr("RB30=");

    sendByte(PORTBbits.RB3 + '0');
    sendByte(PORTBbits.RB2 + '0');
    sendByte(PORTBbits.RB1 + '0');
    sendByte(PORTBbits.RB0 + '0');

    sendByte('\n');

    IFS0bits.T1IF = 0;
}

void initialize()
{
    //2hz will be obtained using T1 interrupts
    T1CONbits.TCKPS = 3; //256
    PR1 = 39061;
    TMR1 = 0;
    T1CONbits.ON = 1;

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    //UART CONFIGURATION
    U2BRG = 1041;
    U2MODEbits.BRGH = 0; //divide by 16
    U2MODEbits.PDSEL = 0; // 8 bits - no parity
    U2MODEbits.STSEL = 0; //1 stop bit

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 0;

    U2MODEbits.ON = 1;

    EnableInterrupts();




}

int main(void)
{
    initialize();
    while(TRUE);
}