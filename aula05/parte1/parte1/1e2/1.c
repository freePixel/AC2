#include <detpic32.h>

#define K 20000

void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < K * ms);
} 


void send2displays(unsigned char value)
{
	static const char display7Scodes[] = {0x3f , 0x6b , 0x5b};
	
	//select display high
	LATDbits.LATD6 = 1;
	LATDbits.LATD5 = 0;

	LATB = (LATB & 0xffff80ff) | ((display7Scodes[value >> 4]) << 8);

	LATDbits.LATD6 = 0;
	LATDbits.LATD5 = 1;

	LATB = (LATB & 0xffff80ff) | ((display7Scodes[value & 0x0f]) << 8);
	
}

int main(void)
{
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;

	TRISB = TRISB & 0xffff80ff;

	while(1)
	{
		send2displays(0x15);
		delay(200);
	}

}
