
#include <detpic32.h>

//4us a 1
//aula anterior 3.6us
//-> 0.4us de latencia logo cycles = 16 ciclos

void _int_(27) isr_adc(void)
{

    volatile int value;
    LATDbits.LATD11 = 0;
    value = *(int*)(&ADC1BUF0);
    AD1CON1bits.ASAM = 1;
    LATDbits.LATD11 = 1;
    IFS1bits.AD1IF = 0;
}

int main(void)
{
    TRISDbits.TRISD11 = 0;

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;


    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    AD1CON1bits.ASAM = 1;
    while(1);
    return 0;



}