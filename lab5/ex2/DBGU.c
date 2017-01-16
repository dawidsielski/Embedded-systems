#include "AT91SAM9263.h"
#include "DBGU.h"

void DBGUInit()
{
  DisableDBGUInterrupts();
  TurnReceiverOff();
  ResetReceiver();
  TurnTransmitterOff();
  ResetTransmitter();
  SetReceiverAndTransmitterOutput();
  SetBaudrate();
  Configure8N1();
  TurnReceiverOn();
  TurnTransmitterOn();
}

void DisableDBGUInterrupts()
{
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_RXRDY;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_TXRDY;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_ENDRX;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_ENDTX;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_OVRE;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_FRAME;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_PARE;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_TXEMPTY;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_TXBUFE;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_RXBUFF;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_COMM_TX;
  AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_COMM_RX;
}
void TurnReceiverOff()
{
  AT91C_BASE_DBGU->DBGU_CR=AT91C_US_RSTRX;
}
void ResetReceiver()
{
  AT91C_BASE_DBGU->DBGU_CR=AT91C_US_RXDIS;
}
void TurnTransmitterOff()
{
  AT91C_BASE_DBGU->DBGU_CR=AT91C_US_TXDIS;
}
void ResetTransmitter()
{
  AT91C_BASE_DBGU->DBGU_CR=AT91C_US_RSTTX;
}
void TurnReceiverOn()
{
  AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXEN; 
}
void TurnTransmitterOn()
{
  AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN;
}
void SetReceiverAndTransmitterOutput()
{
  AT91C_BASE_PIOC->PIO_ASR = AT91C_PC30_DRXD;
  AT91C_BASE_PIOC->PIO_PDR = AT91C_PC30_DRXD;

  AT91C_BASE_PIOC->PIO_ASR = AT91C_PC31_DTXD;
  AT91C_BASE_PIOC->PIO_PDR = AT91C_PC31_DTXD;
}
void SetBaudrate()
{
  AT91C_BASE_DBGU->DBGU_BRGR = (int)(MASTERCLOCK/(16*BAUDRATE));
}
void Configure8N1()
{
  AT91C_BASE_DBGU->DBGU_MR = AT91C_US_CHMODE_NORMAL;
  AT91C_BASE_DBGU->DBGU_MR = AT91C_US_PAR_NONE;
}
int CheckIfReadyForTransfer()
{
	return (!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY));
}
void SendChar(char letter)
{
  while(CheckIfReadyForTransfer()){} 
  AT91C_BASE_DBGU->DBGU_THR = (unsigned int)letter;
}
void DBGUprintAscii(char* buffer)
{
  while(*buffer != '\0'){
	SendChar(*buffer);
	buffer++;
  }
}
int CheckIfReadyToRecive()
{
	return (!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY));
}
unsigned char ReadChar()
{
  while(CheckIfReadyToRecive()){}
  return AT91C_BASE_DBGU->DBGU_RHR; 
}

void Capitalize_Ascii(unsigned char* buffer)
{
  while(*buffer){
    if(*buffer >= 'a' && *buffer <= 'z')
    *buffer -= OFFSET;
    else if (*buffer >= 'A' && *buffer <= 'Z')
    *buffer += OFFSET;
    SendChar(*buffer);
    buffer++;
  }
}
