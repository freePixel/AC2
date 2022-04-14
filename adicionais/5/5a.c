#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    int counter = 0;


    while(1)
    {

        printInt(counter , 10 | (2 << 16));
        putChar('\r');

        counter = (counter + 1 ) % 100;
        delay(100);
    }
}