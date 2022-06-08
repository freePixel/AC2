#include <detpic32.h>

#define TRUE 1
#define FALSE 0













volatile int voltage = 0;
volatile int minVoltage =  33;
volatile int maxVoltage = 0;


unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}



void putc(char byte)
{
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void putStrInt(char *s)
{
    int i=0;
    while(*(s+i) != '\0')
    {
        putc(*(s+i));
        i++;
    }
}






void _int_(32) isr_uart2(void)
{
    if(IFS1bits.U2RXIF == 1)
    {
        char c = U2RXREG;
        putStrInt("VMxx=");
        int value;
        if(c == 'M') value = maxVoltage;
        if(c == 'm') value = minVoltage;
        

        if(c == 'M' || c == 'm')
        {
            value = toBcd(value);
            value &= 0x000000ff;
            char d1 = (value >> 4) + '0';
            char d2 = (value & 0x0f) + '0';
            putc(d1);
            putc(d2);
            putc('\n');
        }
        IFS1bits.U2RXIF = 0;
    }

    

}







void send2displays(unsigned char value , int active)
{
    static const char display7Scodes[] = {0x3f , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d , 0x7d , 0x07 , 0x7f , 0x6f , 0x77 , 0x7c , 0x39 , 0x5e , 0x79 , 0x71};
    static char displayFlag = 0;
    
    unsigned char digit_low;
    unsigned char digit_high;

    if(active)
    {
        digit_low = value & 0x0f;
        digit_high = value >> 4;

        if(displayFlag)
        {
            LATB = (LATB & 0xffff80ff) | (display7Scodes[digit_low] << 8);
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
        }
        else{
            LATB = (LATB & 0xffff80ff) | (display7Scodes[digit_high] << 8);
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
        }

        displayFlag = !displayFlag;
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 0;
    }
}




void _int_(27) isr_adc(void)
{
    int j = 0;
    int arr[8];
    int* p = (int*)(&ADC1BUF0);
    for(j=0;j<8;j++)
    {
        arr[j] = (p[j*4]*33+511)/1023;
    }
    voltage = (arr[0]+arr[1]+arr[2]+arr[3]+arr[4]+arr[5]+arr[6]+arr[7]) / 8;

    if(voltage < minVoltage) minVoltage = voltage;
    if(voltage > maxVoltage) maxVoltage = voltage;




    IFS1bits.AD1IF = 0;
}

void _int_(4) isr_T1(void)
{
    AD1CON1bits.ASAM = 1;
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void)
{
    
    send2displays(toBcd(voltage) , TRUE);
    IFS0bits.T3IF = 0;
}








void initialize()
{
    //initialize display
    TRISB = TRISB & 0xffff80ff;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;

    //initialize ADC
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 7;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;


    IPC6bits.AD1IP = 2;
    IEC1bits.AD1IE = 1;
    IFS1bits.AD1IF = 0;

    //initialize T3
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;


    //initialize T1
    T1CONbits.TCKPS = 2;
    PR1 = 62499;
    TMR1 = 0;

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    T1CONbits.TON = 1;

    //configure UART
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    //configure UART INTERRUPTS

    U2STAbits.UTXISEL = 0;
    U2STAbits.URXISEL = 0;

    IPC8bits.U2IP = 2;
    IEC1bits.U2RXIE = 1;
    IFS1bits.U2RXIF = 0;

    IEC1bits.U2TXIE = 0;
    IFS1bits.U2TXIF = 0;

    EnableInterrupts();

}

int main(void)
{

    
    initialize();
    
    while(1);

    return 0;
}