#include <detpic32.h>

typedef struct
{
    char mem[100];
    int nchar;
    int posrd;
} t_buf;

volatile t_buf txbuf;

void putStrInt(char *s)
{
    while(txbuf.nchar > 0);
    int i=0;
    while(*(s+i) != '\0')
    {
        txbuf.mem[i] = *(s+i);
        txbuf.nchar++;
        i++;
    }
    txbuf.posrd = 0;
    IEC1bits.U2TXIE = 1;

}

void putc(char byte)
{
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void _int_(32) isr_uart2(void)
{
    if(IFS1bits.U2TXIF == 1)
    {
        if(txbuf.nchar > 0)
        {
            U2TXREG = txbuf.mem[txbuf.posrd++];
            txbuf.nchar--;
        }
        else{
            IEC1bits.U2TXIE = 0;
        }
    }

    IFS1bits.U2TXIF = 0;

}

void initialize()
{
    //configure led
    TRISCbits.TRISC14 = 0;
    LATCbits.LATC14 = 0;
    //configure UART
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    //configure UART INTERRUPTS

    U2STAbits.UTXISEL = 0;
    U2STAbits.URXISEL = 0;

    IPC8bits.U2IP = 2;
    IEC1bits.U2RXIE = 1;
    IFS1bits.U2RXIF = 0;

    IEC1bits.U2TXIE = 1;
    IFS1bits.U2TXIF = 0;

    EnableInterrupts();
}


int main(void)
{
    
    initialize();

    while(1)
    {
        putStrInt("abcd\n");
        resetCoreTimer();
        while(readCoreTimer() < 20000 * 1000);
    }
    return 0;
}