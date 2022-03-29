#define __LANGUAGE_C__ //se o intelliSense não reconhecer __PORTEbits_t , ...  (ignorar aviso gerado com o pcompile)
#include <detpic32.h>  //se o IDE nao detetar <detpic32.h> deve-se adicionar "/opt/pic32mx/include" no include path


int main(void)
{
    TRISB = TRISB & 0xffff80ff;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1)
    {
        char s = getChar();

        LATB = (LATB & 0xffff80ff);

        switch(s)
        {
            case 'a': LATBbits.LATB8 = 1; break;
            case 'b': LATBbits.LATB9 = 1; break;
            case 'c': LATBbits.LATB10 = 1; break;
            case 'd': LATBbits.LATB11 = 1; break;
            case 'e': LATBbits.LATB12 = 1; break;
            case 'f': LATBbits.LATB13 = 1; break;
            case 'g': LATBbits.LATB14 = 1; break;

        }
    }
}