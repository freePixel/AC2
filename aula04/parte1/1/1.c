#define __LANGUAGE_C__ //se o intelliSense não reconhecer __PORTEbits_t , ...  (ignorar aviso gerado com o pcompile)
#include <detpic32.h>  //se o IDE nao detetar <detpic32.h> deve-se adicionar "/opt/pic32mx/include" no include path

#define K 20000

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < K * ms);
} 

int main(void)
{

    TRISCbits.TRISC14 = 0;

    while(1)
    {
        delay(500);
        LATCbits.LATC14 = !LATCbits.LATC14;
    }
    return 0;
    
}