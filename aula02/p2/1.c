

void delay(unsigned int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < 20000  * ms);
}

int main(void)
{
	int cnt1 = 0;
	int cnt5 = 0;
	int cnt10 = 0;
	int delay_time = 100;
	while(true)
	{
		char s = inkey();
		if(s == 'A')
			delay_time = 200;
		if(s == 'N')
			delay_time = 100;	
			

		if(cnt10 % 10 == 0)
			cnt1++;
		if(cnt10 % 2 == 0)
			cnt5++;
		cnt10++;

		putChar('\r');
		printInt(cnt10 , 10 | 5 << 16);
		putChar(' ');
		printInt(cnt5 , 10 | 5 << 16);
		putChar(' ');
		printInt(cnt1 , 10 | 5 << 16);
		delay(delay_time);
	}

	return 0;
}
