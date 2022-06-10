#include <detpic32.h>


#define BUFFER_SIZE 16
#define TRUE 1
#define FALSE 0

typedef struct
{
	unsigned char data[BUFFER_SIZE];
	unsigned int position;
	unsigned int size;
} buffer;


volatile buffer tx_buf;

void put(unsigned char value)
{
	if(tx_buf.position == BUFFER_SIZE - 1)
		tx_buf.position = 0;
	else{
		tx_buf.position++;
	}
	tx_buf.data[tx_buf.position] = value;

	if(tx_buf.size < BUFFER_SIZE)
		tx_buf.size++;
	
}


void putc(char byte)
{
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void putstr(char *str)
{
    char* iter = str;
    while(*iter != '\0')
    {
        putc(*iter);
        iter++;
    }
}


void _int_(32) isr_uart2()
{

	if(IFS1bits.U2RXIF == 1)
	{
		
		if(U2RXREG == 'D')
		{
			
			putstr("#elem:");
			if(tx_buf.size >= 10) putc('1');
			putc(tx_buf.size % 10 + '0');
			putc('-');
			int i , j;
			for(i=0;i<tx_buf.size;i++)
			{
				char value = tx_buf.data[(tx_buf.position - i) % BUFFER_SIZE];
				
				putc(((value & 0x8) >> 3) + '0');
				putc(((value & 0x4) >> 2) + '0');
				putc(((value & 0x2) >> 1) + '0');
				putc(( value & 0x1      ) + '0');

				if(i < tx_buf.size - 1) putc(',');
			}



			putc('\n');

			//CLEAR BUFFER
			tx_buf.size = 0;
			tx_buf.position = 0;

			
		}

		IFS1bits.U2RXIF = 0;
	}
}

void initialize()
{
	tx_buf.position = 0;
	tx_buf.size = 0;
	//RB0-RB3 PORTS CONFIGURED AS INPUT
	TRISB |= 0xf;

	//UART2 CONFIGURATION
	U2BRG = 86;
	U2MODEbits.BRGH = 1;
	U2MODEbits.PDSEL = 2;
	U2MODEbits.STSEL = 0;

	U2STAbits.UTXEN = 1;
	U2STAbits.URXEN = 1;

	U2MODEbits.ON = 1;
	
	IPC8bits.U2IP = 2;
	IEC1bits.U2RXIE = 1;
	IFS1bits.U2RXIF = 0;



	EnableInterrupts();

}


int main(void)
{
	initialize();
	while(TRUE)
	{
		if(readCoreTimer() >= 13333333)
		{
			resetCoreTimer();
			char read = (char)(PORTB & 0x0f);
			put(read);
			
		}
	}
}
