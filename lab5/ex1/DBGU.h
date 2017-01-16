#include "AT91SAM9263.h"
#define MASTERCLOCK 100000000
#define BAUDRATE 115200
#define OFFSET 32

void DBGUInit();
void SendChar(char letter);
unsigned char ReadChar();
void DBGUprintAscii(char* buffer);
void Capitalize_Ascii(unsigned char* buffer);

void DisableDBGUInterrupts();
void TurnReceiverOff();
void ResetReceiver();
void TurnTransmitterOff();
void ResetTransmitter();
void SetReceiverAndTransmitterOutput();
void SetBaudrate();
void Configure8N1();
void TurnReceiverOn();
void TurnTransmitterOn();
