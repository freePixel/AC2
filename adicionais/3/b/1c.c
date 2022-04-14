#include <detpic32.h>


int main(void)
{
    TRISB = TRISB | 0x000f;

    TRISE = TRISE & 0xff00;

    while(1)
    {

        LATE = (LATE & 0xfff0) | ((PORTB & 0x000f) ^ 0x000f);
        LATE = (LATE & 0xff0f) | (((PORTB & 0x0001) << 7) | ((PORTB & 0x0002) << 5) | ((PORTB & 0x0004) << 3) | ((PORTB & 0x0008) << 1));
    }

    return 0;
}

