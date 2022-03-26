#define __LANGUAGE_C__ //se o intelliSense não reconhecer __PORTEbits_t , ...  (ignorar aviso gerado com o pcompile)
#include <detpic32.h>  //se o IDE nao detetar <detpic32.h> deve-se adicionar "/opt/pic32mx/include" no include path

#define K (PBCLK / 1000) 

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < K * ms);
} 

int main(void)
{
    unsigned int counter = 0;
   

   TRISE = (TRISE & 0xFFF0);

    while(1)
    {
        counter = counter & 0xf;        //previne a escrita em bits superiores a 3 do LATE
        LATE = (LATE & 0xfff0) | counter;

        counter++;
        if(counter > 15) counter = 0;
        delay(250);
    }
    

    return 0;
}