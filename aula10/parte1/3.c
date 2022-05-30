#include <detpic32.h>

#define TRUE  1
#define FALSE 0
// baurate = 115200 bps

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
    //UART CONFIGURATION
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    //TIMER CONFIGURATION
    T3CONbits.TCKPS = 7;
    PR3 = 39061;
    TMR3 = 0;
    T3CONbits.TON = 1;
    int cnt = TRUE;

    while(TRUE)
    {
        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0;
        if(cnt == TRUE) cnt = FALSE;
        else{
            putstr("String de teste\n"); 
            cnt = TRUE;
        }
    }

    return 0;

}