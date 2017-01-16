#include "AT91SAM9263.h"
#define BAUDRATE 115200
#define MASTERCLOCK 100000000
#define ALL_INTERRUPTS 0xFFFFFFFF
#define ENTER 13

void DBGU_init(void);
void sendChar(char letter);
void printCharacter(unsigned char* buffer);
void DisplayFromFIFO();
void ReadFromFIFO();
