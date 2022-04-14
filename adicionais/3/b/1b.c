#include <detpic32.h>


int main(void)
{

    TRISB = TRISB | 0x000f;


    TRISE = TRISE & 0xfff0;

    while(1)
    {
        LATE = (LATE & 0xfff0) | (((PORTB & 0x0001) << 3) | ((PORTB & 0x0002) << 1) | ((PORTB & 0x0004) >> 1) | ((PORTB & 0x0008) >> 3));
    }

    return 0;
}

