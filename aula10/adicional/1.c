#include <detpic32.h>

void configUart2(unsigned int baud , char parity , unsigned int stopbits)
{
    unsigned int real_baud = baud;
    char real_parity = parity;
    unsigned int real_stopbits = stopbits;
    if(baud < 600 || baud > 115200 || (parity != 'N' && parity != 'E' && parity != 'O') || (stopbits != 1 && stopbits != 2))
    {
        real_baud = 115200;
        real_parity = 'N';
        real_stopbits = 1;
    }
    //UART2 CONFIGURATION
    U2BRG = 20000000 / (16 * real_baud);

    U2MODEbits.BRGH = 0;
    switch(real_parity)
    {
        case 'N': U2MODEbits.PDSEL = 0; break;
        case 'E': U2MODEbits.PDSEL = 1; break;
        case 'O': U2MODEbits.PDSEL = 2; break;
    }

    U2MODEbits.STSEL = real_stopbits - 1;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;
}


void putc(char byte)
{
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void putstr(char *str)
{
    char* iter = str;
    while(*iter != '\0')
    {
        putc(*iter);
        iter++;
    }
}

int main(void)
{
    T3CONbits.TCKPS = 7;
    PR3 = 39061;
    TMR3 = 0;
    T3CONbits.TON = 1;

    configUart2(600, 'N' , 2);

    while(1)
    {
        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0;

        putstr("String de teste!\n");
    }
}