#include <detpic32.h>


int main(void)
{

    TRISE = TRISE & 0xfff0;


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
                LATE = (LATE & 0xfff0) | (0x0001);
                break;

            case '1':
                LATE = (LATE & 0xfff0) | (0x0002);
                break;

            case '2':
                LATE = (LATE & 0xfff0) | (0x0004);
                break;

            case '3':
                LATE = (LATE & 0xfff0) | (0x0008);
                break;

            case '\0':

            break;

            default:
                LATE = (LATE & 0xfff0) | (0x000f);

                resetCoreTimer();
                while(readCoreTimer() < 20000000);

                LATE = (LATE & 0xfff0);
                break;
        }
    }

    return 0;
}

