    	void dbgu_print_ascii(const char *a) {}
       
	// BUTTON
        volatile unsigned int *ptrPIOB_PER = (volatile unsigned int *) 0xFFFFF400; // enable register
        volatile unsigned int *ptrPIOB_OER = (volatile unsigned int *) 0xFFFFF410; // output enable
        volatile unsigned int *ptrPIOB_SODR = (volatile unsigned int *) 0xFFFFF430; // set turns off
        volatile unsigned int *ptrPIOB_CODR = (volatile unsigned int *) 0xFFFFF434; // clear - turns on
     
        volatile unsigned int *ptrPIOC_ODR = (volatile unsigned int *) 0xFFFFF614; // button - output disable
        volatile unsigned int *ptrPIOC_PDSR = (volatile unsigned int *) 0xFFFFF63C; // PIN data status register
        // DIODE
        volatile unsigned int *ptrPIOC_PER = (volatile unsigned int *) 0xFFFFF600; // enable register led pin I/O
        volatile unsigned int *ptrPIOC_OER = (volatile unsigned int *) 0xFFFFF610; // output enable control
        volatile unsigned int *ptrPIOC_SODR = (volatile unsigned int *) 0xFFFFF630; // set turns off
        volatile unsigned int *ptrPIOC_CODR = (volatile unsigned int *) 0xFFFFF634; // clear - turns on
     
	#define SET_29BIT_DS2 (1 << 29)
	#define SET_8BIT_DS1 (1 << 8)
	#define SET_5BIT_RIGHT_CLICK (1 << 5)
	#define SET_4BIT_LEFT_CLICK (1 << 4)
	

    void initialize()
    {
        *ptrPIOC_PER = SET_29BIT_DS2;
        *ptrPIOC_OER = SET_29BIT_DS2;
        *ptrPIOB_PER = SET_8BIT_DS1;
        *ptrPIOB_OER = SET_8BIT_DS1;
        *ptrPIOC_ODR = SET_5BIT_RIGHT_CLICK;
        *ptrPIOC_ODR = SET_4BIT_LEFT_CLICK;
    }

	#define DELAY 50000
    int main()
    {
	int counter = 0;
	int if_on = 0;
    initialize();
    while(1)
	{
		counter++;
		
		if(counter % 5000 == 0)
		{
			if(!(*ptrPIOC_PDSR & SET_4BIT_LEFT_CLICK))
			{
				*ptrPIOB_SODR = SET_8BIT_DS1;
			}
			if(!(*ptrPIOC_PDSR & SET_5BIT_RIGHT_CLICK))
			{
				*ptrPIOB_CODR = SET_8BIT_DS1;
			}
		}
		if(counter == DELAY)
		{
			if(if_on)
			{
				*ptrPIOC_SODR = SET_29BIT_DS2;
				if_on = 0;
			}
			else
			{
				*ptrPIOC_CODR = SET_29BIT_DS2;
				if_on = 1;
			}
			counter = 0;
		}
	}
    }
