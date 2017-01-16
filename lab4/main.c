    #include "AT91SAM9263.h"
	void dbgu_print_ascii(const char *a) {}
       
	// DIODE
	volatile unsigned int *ptrPIOC_PER = (volatile unsigned int *) 0xFFFFF600; // enable register led pin I/O
	volatile unsigned int *ptrPIOC_OER = (volatile unsigned int *) 0xFFFFF610; // output enable control
	volatile unsigned int *ptrPIOC_SODR = (volatile unsigned int *) 0xFFFFF630; // set turns off
	volatile unsigned int *ptrPIOC_CODR = (volatile unsigned int *) 0xFFFFF634; // clear - turns on

	#define SET_29BIT_DS2 (1 << 29)
	#define SET_8BIT_DS1 (1 << 8)
	#define SET_5BIT_RIGHT_CLICK (1 << 5)
	#define SET_4BIT_LEFT_CLICK (1 << 4)

	#define SET_COUNTER 6250

	void init_PIT()
	{
		AT91C_BASE_PITC->PITC_PIMR = SET_COUNTER;
		AT91C_BASE_PITC->PITC_PIMR &= ~AT91C_PITC_PITEN; //disable clock
		AT91C_BASE_PITC->PITC_PIMR &= ~AT91C_PITC_PITIEN; //disable interrupt
		AT91C_BASE_PITC->PITC_PIVR;
	}
	void timer_enable()
	{
		AT91C_BASE_PITC->PITC_PIMR |= AT91C_PITC_PITEN;
	}
	void timer_disable()
	{
		AT91C_BASE_PITC->PITC_PIMR &= ~AT91C_PITC_PITEN;
	}
	void clear_PITS()
	{
		AT91C_BASE_PITC->PITC_PIVR;
	}
	int check_PITS_FLAG()
	{
		return AT91C_BASE_PITC->PITC_PISR;
	}

	void delay(int ms)
	{
		volatile unsigned int i;
		volatile unsigned int status = 0;
		for(i = 0; i < ms; i++) 
		{
			timer_enable();
			while(1)
			{
					status = AT91C_BASE_PITC->PITC_PIIR;
					if(check_PITS_FLAG())
					{
						clear_PITS();
						break;
					}
				}
			}
			timer_disable();
	}
	
	void diode_ON()
	{
		*ptrPIOC_CODR = SET_29BIT_DS2;
	}
	void diode_OFF()
	{
		*ptrPIOC_SODR = SET_29BIT_DS2;
	}

	void initialize()
	{
		*ptrPIOC_PER = SET_29BIT_DS2;
		*ptrPIOC_OER = SET_29BIT_DS2;
		*ptrPIOC_SODR = SET_29BIT_DS2;
	}

	int main()
	{
		initialize();
		init_PIT();
		while(1)
		{
			diode_ON();
			delay(500);
			diode_OFF();
			delay(500);
		}

	}
