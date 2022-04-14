#include <detpic32.h>


int main(void)
{

    TRISB = TRISB | 0x000f;


    TRISE = TRISE & 0xfff0;

    while(1)
    {
        LATE = (LATE & 0xfff0) | (PORTB & 0x000f);
    }

    return 0;
}