void dbgu_print_ascii(const char *buffer){}

#include "DBGU.c"
#define CAPITALIZE_OFFSET -32

void SendAlphabet()
{
  int letter = 'a';
  while(letter <= 'z'){
    SendChar((char)letter);
    letter++;
  }
} 

void CapitalizeInput()
{
  char letter = ReadChar();
  if(letter >= 'a' && letter <= 'z')
  letter -= OFFSET;
  else if (letter >= 'A' && letter <= 'Z')
  letter += OFFSET;
  SendChar(letter);  
}

int main()
{
  DBGUInit();
  DBGUprintAscii("Hello world\r\n");
  Capitalize_Ascii((unsigned char*)"THIS TEXT SHOULD BE WRITTEN IN SMALL LETTERS\r\n");
  Capitalize_Ascii((unsigned char*)"this should be big letters\r\n");
  SendAlphabet();
  while(1){
    CapitalizeInput();
  } 
}
