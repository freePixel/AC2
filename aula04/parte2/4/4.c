
#include <detpic32.h> 



#define K 20000

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < K * ms);
} 



int main(void)
{

    unsigned char seg;

    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    TRISB = TRISB & 0xffff80ff;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    int i=0;

    while(1)
    {
        
        seg = 1;
        for(i=0;i<7;i++)
        {

            delay(100); //50hz -> 20 , 100hz -> 10

            LATB = (LATB & 0xffff80ff) | (seg << 8);

            seg = seg << 1;
        }

        LATD = (LATD) ^ (0x0000000);
    }

    return 0;





}