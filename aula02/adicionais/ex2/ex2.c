

int main(void)
{
	int cnt1 = 0;
	int cnt5 = 0;
	int cnt10 = 0;

	while(true)
	{
		if(timeDone(100 , 0) > 0)
		{
		timeDone(0 , 1); //reset
		cnt10++;
		if(cnt10 % 10 == 0) cnt1++;
		if(cnt5  %  2 == 0) cnt5++;
		
		putChar('\r');
		printInt(cnt10 , 10 | 5 << 16);
		putChar(' ');
		printInt(cnt5 ,  10 | 5 << 16);
		putChar(' ');
		printInt(cnt1 ,  10 | 5 << 16);

		}
	}

	return 0;
}
