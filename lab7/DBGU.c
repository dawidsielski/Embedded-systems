#include "AT91SAM9263.h"
#include "DBGU.h"
#include "FIFO.h"

void DBGU_init(void)
{
	AT91C_BASE_DBGU->DBGU_IDR = ALL_INTERRUPTS;															//deactivate all interrupts
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RSTRX | AT91C_US_RXDIS;							//reset and turn off receiver
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RSTTX | AT91C_US_TXDIS;							//reset and turn off transmitter
	AT91C_BASE_PIOC->PIO_ASR = AT91C_PC31_DTXD;															//enables peripheral control to transmitter
	AT91C_BASE_PIOC->PIO_PDR = AT91C_PC31_DTXD;															//assigns I/O line to transmitter
	AT91C_BASE_DBGU->DBGU_BRGR = MASTERCLOCK/(16*BAUDRATE);									//configure throughout
	AT91C_BASE_DBGU->DBGU_MR= AT91C_US_CHMODE_NORMAL |  AT91C_US_PAR_NONE;	//operation mode
	//AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN;															//turn on transmitter
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXEN;																//turn on receiver
}

void sendChar(char letter)
{
	while(!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY));
	AT91C_BASE_DBGU->DBGU_THR = (unsigned int)letter;
}

char readChar()
{
	while(!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY));
	return AT91C_BASE_DBGU->DBGU_RHR;
}

void printCharacter(unsigned char* buffer)
{
  while(*buffer != '\0'){
    sendChar(*buffer);
    buffer++;
  }  
}

void DisplayFromFIFO()
{
	char readData;
	if(FifoGet(&readData))
	    sendChar(readData);
	else
	{ 
		printCharacter((unsigned char*)"\n\r");
		AT91C_BASE_DBGU->DBGU_CR=AT91C_US_TXDIS;
	}
}

void ReadFromFIFO()
{
	char input = readChar();
	int full;
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN;
	sendChar(input);
	AT91C_BASE_DBGU->DBGU_CR=AT91C_US_TXDIS;
	if(input == ENTER)
	{
		AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN;
		printCharacter((unsigned char*)"\n\r");
	}
	else
	{
		full = FifoPut(input);
		if(full == 0)
		{
			AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN;
			printCharacter((unsigned char*)"\n\rFifo overflow!\n\r");
		}
	}
}

