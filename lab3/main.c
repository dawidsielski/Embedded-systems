    void dbgu_print_ascii(const char *a) {}
       
	
    volatile unsigned int *ptrPIOB_PER = (volatile unsigned int *) 0xFFFFF400; // enable register
    volatile unsigned int *ptrPIOB_OER = (volatile unsigned int *) 0xFFFFF410; // output enable
    volatile unsigned int *ptrPIOB_SODR = (volatile unsigned int *) 0xFFFFF430; // set turns off
    volatile unsigned int *ptrPIOB_CODR = (volatile unsigned int *) 0xFFFFF434; // clear - turns on
    
    #define SEG_A 1<<25
    #define SEG_B 1<<24
    #define SEG_C 1<<22
    #define SEG_D 1<<21
    #define SEG_E 1<<20
    #define SEG_F 1<<27
    #define SEG_G 1<<26

    #define RIGHT_DISPLAY 1<<30
    #define LEFT_DISPLAY 1<<28

    #define SET_BRIGHTNESS 1<<29

    #define TIME_OF_DISPLAY_SINGLE_DIGIT 10
    #define TIME_FOR_DISPLAY_ONE_NUMBER 50
    
    void enable_right_display()
    {
	*ptrPIOB_CODR = RIGHT_DISPLAY;
    }
    void disable_right_display()
    {
	*ptrPIOB_SODR = RIGHT_DISPLAY;
    }
    void enable_left_display()
    {
	*ptrPIOB_CODR = LEFT_DISPLAY;
    }
    void disable_left_display()
    {
	*ptrPIOB_SODR = LEFT_DISPLAY;
    }
    void initialize_displays()
    {
	*ptrPIOB_PER = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SET_BRIGHTNESS;
	*ptrPIOB_OER = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SET_BRIGHTNESS;
	*ptrPIOB_CODR = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SET_BRIGHTNESS;
	disable_right_display();
	disable_left_display();
	
    }
    void zero()
    {
	*ptrPIOB_SODR = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
    }
    void one()
    {
	*ptrPIOB_SODR = SEG_B | SEG_C;
    }
    void two()
    {
	*ptrPIOB_SODR = SEG_A | SEG_B | SEG_D | SEG_E | SEG_G;
    }
    void three()
    {
	*ptrPIOB_SODR = SEG_A | SEG_B | SEG_C | SEG_D | SEG_G;
    }
    void four()
    {
	*ptrPIOB_SODR =  SEG_B | SEG_C | SEG_F | SEG_G;
    }
    void five()
    {
	*ptrPIOB_SODR = SEG_A | SEG_C | SEG_D | SEG_G | SEG_F;
    }
    void six()
    {
	*ptrPIOB_SODR = SEG_A | SEG_C | SEG_D | SEG_G | SEG_F | SEG_E;
    }
    void seven()
    {
	*ptrPIOB_SODR = SEG_A | SEG_B | SEG_C;
    }
    void eight()
    {
	*ptrPIOB_SODR = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
    }
    void nine()
    {
	*ptrPIOB_SODR = SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G;
    }
    void clear_all()
    {
	*ptrPIOB_CODR = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
    }
    void delay(int ms)
    {
      	volatile unsigned int i;
	for(i = 0; i < 1000 * ms; i++) {}
    }

    void show_digit(int digit)
    {
	switch(digit){
		case 0:
		zero();
		break;
		case 1:
		one();
		break;
		case 2:
		two();
		break;
		case 3:
		three();
		break;
		case 4:
		four();
		break;
		case 5:
		five();
		break;
		case 6:
		six();
		break;
		case 7:
		seven();
		break;
		case 8:
		eight();
		break;
		case 9:
		nine();
		break;
	}
    }

    void display_number(int number)
    {
		int first_digit = number / 10,
		    second_digit = number % 10,
		    i;
		for(i = 0; i < TIME_FOR_DISPLAY_ONE_NUMBER; i++)
		{
			  show_digit(first_digit);
			  enable_left_display();
			  delay(TIME_OF_DISPLAY_SINGLE_DIGIT);
			  disable_left_display();
			  clear_all();
	
			  show_digit(second_digit);
			  enable_right_display();
			  delay(TIME_OF_DISPLAY_SINGLE_DIGIT);
			  disable_right_display();
			  clear_all();
		}
    }
    
    
    int main()
    {
	initialize_displays();
	int number = 0;
	while(1)
	{
		for(number = 0; number < 100; number++)
		{
			display_number(number);
		}
	}
	
	while(1);
	
    }
