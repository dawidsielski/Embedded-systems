void dbgu_print_ascii(const char *buffer){}

#include "DBGU.h"
#include "FIFO.h"
#define CAPITALIZE_OFFSET -32

void SendAlphabet(){
  int letter = 'a';
  while(letter <= 'z'){
    SendChar((char)letter);
    letter++;
  }
} 

void CapitalizeEcho()
{
  char letter = ReadChar();
  if(letter >= 'a' && letter <= 'z')
  letter -= OFFSET;
  else if (letter >= 'A' && letter <= 'Z')
  letter += OFFSET;
  SendChar(letter);  
}

void TransmitToFifo(FIFO *fifo)
{
  int status = CORRECT;
  char letter = 0;
  
  while(letter != '\r'){  
  letter = ReadChar();
    if(letter != '\r'){
      status = FIFOPut(fifo, letter);
			if (status == ERROR){
				DBGUprintAscii((unsigned char*)"Fifo size reached!\n\r");
				letter = '\r';
			}
		}
  }
}

void ReadFromFifo(FIFO *fifo)
{
  char letter = 0;
  
  while(FIFOGet(fifo, &letter) == CORRECT){
    SendChar(letter);
  }
  SendChar('\r');
  SendChar('\n');
}

int main()
{
  FIFO fifo;
  FIFOInit(&fifo);
  DBGUInit();
  DBGUprintAscii("Hello world\r\n");
  Capitalize_Ascii((unsigned char*)"THIS TEXT SHOULD BE WRITTEN IN SMALL LETTERS\r\n");
  Capitalize_Ascii((unsigned char*)"this should be big letters\r\n");
  SendAlphabet();
  while(1){
    TransmitToFifo(&fifo);
    ReadFromFifo(&fifo);
  } 
}
