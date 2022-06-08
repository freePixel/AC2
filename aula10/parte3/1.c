#include <detpic32.h>


void putc(char byte)
{
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void puts(char* str)
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

    //configure UART
    U2BRG = 10; // 65 (19200 bps)
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    //RD11 Output
    TRISDbits.TRISD11 = 0;

    while(1)
    {
        while(U2STAbits.TRMT == 0);
        LATDbits.LATD11 = 1;
        //puts("12345"); //5 , 450 us | 9 , 800us
        puts("123456789AB");
        LATDbits.LATD11 = 0;
    } 
}

/*
115200
                12345       123456789       123456789A      123456789AB
tempo a 1:       3us           5us              90us            180us

tempo a 0:       450us         800us            800us            80us


*/