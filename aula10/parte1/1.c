#include <detpic32.h>

// baurate = 115200 bps


int main(void)
{
    U2BRG = 10;
    U2MODEbits.BRGH = 0; //divide by 16
    U2MODEbits.PDSEL = 0; // 8 bits - no parity
    U2MODEbits.STSEL = 0; //1 stop bit

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;


}