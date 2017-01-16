#include "AT91SAM9263.h"
#include <stdio.h>

#define LED_RIGHT 1 << 29
#define CLOCK 1 << 14
#define DATA 1 << 12
#define CS 1 << 15
#define SLEEP_TIME 1000
#define MS 6250
#define PITS_FLAG 1<<0
#define PITEN (1<<24)
#define PITIEN (1<<25)
#define BAUDRATE 115200
#define MCK 100000000
#define DIVISOR 16
#define TEMP_FACTOR 0.0625
#define PIOB_CLOCK 1 << 3
#define TERMOSTATE_TEMPERATURE 25

short temperature_from_spi = 0;
float real_temperature = 0;

void dbgu_print_ascii(const char *a) {}

void SetClock()
{
	AT91C_BASE_SYS -> SYS_PIOB_SODR = CLOCK;
}

void ClearClock()
{
	AT91C_BASE_SYS -> SYS_PIOB_CODR = CLOCK;
}

void ClearCS()
{
	AT91C_BASE_SYS -> SYS_PIOB_CODR= CS;
}

void SetCS()
{
    AT91C_BASE_SYS -> SYS_PIOB_SODR= CS;
}

void ClearPITS()
{
	AT91C_BASE_PITC-> PITC_PIVR;
}

void InitializeLEDs()
{
	AT91C_BASE_SYS -> SYS_PIOC_PER = LED_RIGHT;
	AT91C_BASE_SYS -> SYS_PIOC_OER = LED_RIGHT;
	AT91C_BASE_SYS -> SYS_PIOC_SODR = LED_RIGHT;
}

void InitializeDBGU(void)
{
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RSTRX | AT91C_US_RXDIS;			//reset and turn off receiver
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RSTTX | AT91C_US_TXDIS;			//reset and turn off transmitter
	AT91C_BASE_PIOC->PIO_ASR = AT91C_PC31_DTXD;					//enables peripheral control to transmitter
	AT91C_BASE_PIOC->PIO_PDR = AT91C_PC31_DTXD;					//assigns I/O line to transmitter
	AT91C_BASE_DBGU->DBGU_BRGR = MCK/(DIVISOR*BAUDRATE);				//configure throughout
	AT91C_BASE_DBGU->DBGU_MR= AT91C_US_CHMODE_NORMAL |  AT91C_US_PAR_NONE;		//operation mode
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN;					//turn on transmitter
}

void InitializePIT()
{
	AT91C_BASE_PITC -> PITC_PIMR = MS;
	AT91C_BASE_PITC -> PITC_PIMR &= ~AT91C_PITC_PITEN;
	AT91C_BASE_PITC -> PITC_PIMR &= ~AT91C_PITC_PITIEN;
	ClearPITS();
}

void InitializePIO()
{
	AT91C_BASE_SYS -> SYS_PIOB_PER = DATA;
	AT91C_BASE_SYS -> SYS_PIOB_PER = CLOCK;
	AT91C_BASE_SYS -> SYS_PIOB_PER = CS;
	AT91C_BASE_SYS -> SYS_PIOB_ODR = DATA; //input
	AT91C_BASE_SYS -> SYS_PIOB_OER = CLOCK;
	AT91C_BASE_SYS -> SYS_PIOB_OER = CS;
	AT91C_BASE_SYS -> SYS_PMC_PCER = PIOB_CLOCK; //enable clock
	SetCS();
	ClearClock();
}

void SendChar(char letter)
{
	while(!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY));
	AT91C_BASE_DBGU->DBGU_THR = (unsigned int)letter;
}

void DisplayString(char* string)
{
	unsigned int i;
	for(i=0; string[i]!='\0'; i++)
	{
		SendChar(string[i]);
	}
}

void Sleep(unsigned int iterations)
{	
	unsigned int i;
	AT91C_BASE_PITC -> PITC_PIMR |= PITEN;
	for (i = 0; i < iterations; i++)
	{
		while(!(AT91C_BASE_PITC -> PITC_PISR & PITS_FLAG)){}
		ClearPITS();
	}
	AT91C_BASE_PITC -> PITC_PIMR &= ~PITEN;
}

void ReadBitFromSpi(int bitNumber)
{
	if(AT91C_BASE_SYS -> SYS_PIOB_PDSR & DATA)
		temperature_from_spi |= 1 << bitNumber;
	else
		temperature_from_spi &= ~(1 << bitNumber);
}

void ReadTemperature()
{
	int i;
	ClearCS();
	for(i = 15; i >= 0; i--)
	{
		SetClock();
		Sleep(1);
		ReadBitFromSpi(i);
		ClearClock();
		Sleep(1);
	}
	SetCS();
	real_temperature = (temperature_from_spi >> 3) * TEMP_FACTOR;
}

void DisplayTemperature()
{
	char tempChar[40];
	sprintf(tempChar, "The temperature now is: %f", real_temperature);
	DisplayString(tempChar);
	DisplayString("\n\r");
}

void LedDS2_ON()
{
	AT91C_BASE_SYS -> SYS_PIOC_CODR =  LED_RIGHT;
}

void LedDS2_OFF()
{
	AT91C_BASE_SYS -> SYS_PIOC_SODR =  LED_RIGHT;
}

void Termostate()
{
	if(real_temperature >= TERMOSTATE_TEMPERATURE)
	    LedDS2_ON();
	else if(real_temperature < TERMOSTATE_TEMPERATURE)
	    LedDS2_OFF();
}

int main()
{
    InitializeLEDs();
    InitializePIO();
    InitializePIT();
    InitializeDBGU();
    
    while(1)
    {
    	ReadTemperature();
    	DisplayTemperature();
    	Termostate();
    	Sleep(SLEEP_TIME);
    }
}
