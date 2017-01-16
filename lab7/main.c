#include "AT91SAM9263.h"
#include "FIFO.h"
#include "DBGU.h"


unsigned int SpuriousInterrupts;
void dbgu_print_ascii(const char *a) {}

void DBGUInterruptHandler(void)
{
	int StatusFlag;
	StatusFlag = AT91C_BASE_DBGU->DBGU_CSR;
	if(StatusFlag & AT91C_BASE_DBGU->DBGU_IMR) 
	{
	    if (StatusFlag & AT91C_US_TXRDY)
      {
          DisplayFromFIFO();
      }
      else if (StatusFlag & AT91C_US_RXRDY)
      {
          ReadFromFIFO();
      }
	}
	else
	{
	    SpuriousInterrupts++;
	}
}

void InitializeDBGUInterrupt()
{
	SpuriousInterrupts = 0;
	AT91C_BASE_AIC -> AIC_IDCR = 1 << AT91C_ID_SYS;
	AT91C_BASE_AIC -> AIC_SVR[AT91C_ID_SYS] = (unsigned int)DBGUInterruptHandler;
	AT91C_BASE_AIC -> AIC_SMR[AT91C_ID_SYS] = AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED | AT91C_AIC_PRIOR_LOWEST;
	AT91C_BASE_AIC -> AIC_ICCR = 1 << AT91C_ID_SYS;
	AT91C_BASE_AIC -> AIC_IECR = 1 << AT91C_ID_SYS;
	AT91C_BASE_DBGU -> DBGU_IER |= AT91C_US_RXRDY;
	AT91C_BASE_DBGU -> DBGU_IER |= AT91C_US_TXRDY;
}

int main()
{
    DBGU_init();
    BufferInit();
    InitializeDBGUInterrupt();
    while(1);
}
 
 
