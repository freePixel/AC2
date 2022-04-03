<<<<<<< HEAD
#define __LANGUAGE_C__
#include <detpic32.h> 

int main(void)
{
    //0111 1111 0000 0000
    TRISB = (TRISB & 0xffff80ff) | 0x00007f00;

=======
#define __LANGUAGE_C__ //se o intelliSense não reconhecer __PORTEbits_t , ...  (ignorar aviso gerado com o pcompile)
#include <detpic32.h>  //se o IDE nao detetar <detpic32.h> deve-se adicionar "/opt/pic32mx/include" no include path


int main(void)
{
    TRISB = TRISB & 0xffff80ff;
>>>>>>> 1116ed5445d22520a6f214b0538289ff329346b2
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
<<<<<<< HEAD
    char s = 'a';
=======

>>>>>>> 1116ed5445d22520a6f214b0538289ff329346b2
    while(1)
    {
        char s = getChar();

<<<<<<< HEAD
        LATB = LATB & 0x80ff;
=======
        LATB = (LATB & 0xffff80ff);

>>>>>>> 1116ed5445d22520a6f214b0538289ff329346b2
        switch(s)
        {
            case 'a': LATBbits.LATB8 = 1; break;
            case 'b': LATBbits.LATB9 = 1; break;
            case 'c': LATBbits.LATB10 = 1; break;
            case 'd': LATBbits.LATB11 = 1; break;
            case 'e': LATBbits.LATB12 = 1; break;
            case 'f': LATBbits.LATB13 = 1; break;
            case 'g': LATBbits.LATB14 = 1; break;
<<<<<<< HEAD
        }
    }

    return 0;


=======

        }
    }
>>>>>>> 1116ed5445d22520a6f214b0538289ff329346b2
}