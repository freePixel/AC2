int main(void)
{
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;
    int arr[4];
    int i = 0;
    while(1)
    {
        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);
        
        int* p = (int*)(&ADC1BUF0);
        for(i=0;i<4;i++)
        {
            arr[i] = (p[i*4]*33+511)/1023;
        }

        int average = (arr[0]+arr[1]+arr[2]+arr[3])/4;

        printInt10(average / 10);
        printStr(".");
        printInt10(average % 10);
        
        printStr("V\n");

        IFS1bits.AD1IF = 0;
    }

    return 0;
}