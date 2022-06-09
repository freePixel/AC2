#include <detpic32.h>





void setPWM(int percentage)
{
    OC3RS = (int)(19999 * (float)percentage / 100);
    OC5RS = (int)(19999 * (float)(100-percentage) / 100);
}

void initialize()
{

    //TIMER 2 CONFIGURATION (USED TO GENERATE 1KHZ PWM SIGNAL)
    T2CONbits.TCKPS = 0;
    PR2 = 19999;
    TMR2 = 0;
    T2CONbits.TON = 1;


    //PWM CONFIGURATION
    OC3CONbits.OCM = 6;
    OC3CONbits.OCTSEL =0;
    OC3RS = 0;
    OC3CONbits.ON = 1;

    //3b
    OC5CONbits.OCM = 6;
    OC5CONbits.OCTSEL = 0;
    OC5RS = 0;
    OC5CONbits.ON = 1;

    //ADC CONFIGURATION
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 3;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;


    TRISCbits.TRISC14 = 0;
    LATCbits.LATC14 = 0;



    EnableInterrupts();
}



int main(void)
{
    
    initialize();
    while(1)
    {
        LATCbits.LATC14 = PORTDbits.RD4; //test without oscilloscope
        if(IFS1bits.AD1IF == 1)
        {
            int* ptr = (int*)(&ADC1BUF0);
            
            int i , s = 0;
            for(i=0;i<4;i++)
                s+= *(ptr + i*4);
            s /= 4;
            setPWM((int)(100.f * ((float)s / 1023)));
            IFS1bits.AD1IF = 0;
        }

        if(readCoreTimer() >= 20000 * 100)
        {
            resetCoreTimer();
            AD1CON1bits.ASAM = 1;
        }
    }
}

