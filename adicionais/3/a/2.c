#include <detpic32.h>


int main(void)
{

    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;


    char s = '\0';
    char u = '\0';
    while(1)
    {
        do{
            s = u;
            u = inkey();
        }
        while(u != '\0');

        switch(s)
        {
            case '0':
                LATEbits.LATE0 = 1;
                LATEbits.LATE1 = 0;
                LATEbits.LATE2 = 0;
                LATEbits.LATE3 = 0;
                break;

            case '1':
                LATEbits.LATE0 = 0;
                LATEbits.LATE1 = 1;
                LATEbits.LATE2 = 0;
                LATEbits.LATE3 = 0;
                break;

            case '2':
                LATEbits.LATE0 = 0;
                LATEbits.LATE1 = 0;
                LATEbits.LATE2 = 1;
                LATEbits.LATE3 = 0;
                break;

            case '3':
                LATEbits.LATE0 = 0;
                LATEbits.LATE1 = 0;
                LATEbits.LATE2 = 0;
                LATEbits.LATE3 = 1;
                break;

            case '\0':

            break;

            default:
                LATEbits.LATE0 = 1;
                LATEbits.LATE1 = 1;
                LATEbits.LATE2 = 1;
                LATEbits.LATE3 = 1;

                resetCoreTimer();
                while(readCoreTimer() < 20000000);

                LATEbits.LATE0 = 0;
                LATEbits.LATE1 = 0;
                LATEbits.LATE2 = 0;
                LATEbits.LATE3 = 0;
                break;
        }
    }

    return 0;
}

