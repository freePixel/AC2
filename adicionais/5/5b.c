#include <detpic32.h>

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void)
{
    int counter = 0;

    char key = '\0';
    int freq = 2;
    int flag = 0;
    while(1)
    {
        flag = 0;
        key = inkey();
        if(key >= '0' && key <= '4')
            freq = 2 * (1 + (key-48));
        


        if(key == '\x0A') //ENTER = 0x0A  
        {
            flag = 1;
        }


        printInt(counter , 10 | (2 << 16));


        if(flag)
        {
            printStr(", ");
            printInt10(freq);
            printStr(" Hz");
        }
        putChar('\r');
        
        counter = (counter + 1 ) % 100;
        delay(1000 / freq);
        printStr("                 ");
        putChar('\r');
    }
}