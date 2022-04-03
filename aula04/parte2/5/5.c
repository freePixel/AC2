
#include <detpic32.h> 



#define K 20000

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < K * ms);
} 

static const char display7Scodes[] = {

    (char)0x3f ,
    (char)0x06 ,
    (char)0x5b ,
    (char)0x4f ,
    (char)0x66 ,
    (char)0x6d ,
    (char)0x7d ,
    (char)0x07 ,
    (char)0x7f ,
    (char)0x6f ,
    (char)0x77 ,
    (char)0x7c ,
    (char)0x39 ,
    (char)0x5e ,
    (char)0x79 ,
    (char)0x71

};

int main(void)
{

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;

    TRISB = TRISB & 0xffff80ff;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    int value = 0;
    while(1)
    {
        
        char seg = display7Scodes[value];

        LATB = (LATB & 0xffff80ff) | (seg << 8);
        
        delay(500);
        
        value++;
        if(value >= 16) value = 0;
    }

    return 0;





}