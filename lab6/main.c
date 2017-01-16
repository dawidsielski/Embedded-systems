void dbgu_print_ascii(const char *a) {}

#include "AT91SAM9263.h"
#include "DiodesAndButtons.h"

int main() 
{
    InitializeDiodesAndButtons();
    InitializeInterrupts();
    while(1){}
}
 


  
