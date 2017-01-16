/**
* Enables or disables LEDs according to the input variable. Bit0 drives LED1, Bit1 drives LED2
* \param state state of the two LEDs
*/
void set_led_state(unsigned char state);

/**
* Sends the bytes from buffer over the UART interface
* \param buffer pointer to the buffer containing the bytes to be sent
*/
void print (const char *buffer); 

/**
* Sends one byte over the UART interface
* \param x the byte to be sent
*/
void outbyte(const char x);

/**
* Receives one byte from the UART interface
* \return the received byte
*/
unsigned char inbyte(void);

/**
* Initializes both LEDs and UART controller
*/
void init_hardware(void);

/**
* Initializes the LEDs controller
*/
void led_init(void); 

/**
* Initializes the UART controller
*/
void configure_dbgu (void);
