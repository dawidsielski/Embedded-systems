    	void dbgu_print_ascii(const char *a) {}
       
	// BUTTON
        volatile unsigned int *ptrPIOC_ODR = (volatile unsigned int *) 0xFFFFF614; // button - output disable
        volatile unsigned int *ptrPIOC_PDSR = (volatile unsigned int *) 0xFFFFF63C; // PIN data status register
        // DIODE
        volatile unsigned int *ptrPIOC_PER = (volatile unsigned int *) 0xFFFFF600; // enable register led pin I/O
        volatile unsigned int *ptrPIOC_OER = (volatile unsigned int *) 0xFFFFF610; // output enable control
        volatile unsigned int *ptrPIOC_SODR = (volatile unsigned int *) 0xFFFFF630; // set turns off
        volatile unsigned int *ptrPIOC_CODR = (volatile unsigned int *) 0xFFFFF634; // clear - turns on
     
    void initialize()
    {
        *ptrPIOC_PER = (volatile unsigned int) 1 << 29;
        *ptrPIOC_OER = (volatile unsigned int) 1 << 29;
        *ptrPIOC_ODR = (volatile unsigned int) 1 << 4;
    }
    void delay()
    {
	    if(!(*ptrPIOC_PDSR & (1 << 4)))
		{
		    *ptrPIOC_CODR = 1 << 29;
		}
	    else
		{
		    *ptrPIOC_SODR = 1 << 29;
		}
    }
    int main()
    {
        initialize();
        while(1){
        delay();
        }
    }
