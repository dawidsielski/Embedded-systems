#include "DiodesAndButtons.h"
#include "AT91SAM9263.h"

unsigned int SpuriousCount = 0;
 
void InitializeDiode1()
{
  AT91C_BASE_PIOB->PIO_PER = AT91C_PIO_PC8;
  AT91C_BASE_PIOB->PIO_OER = AT91C_PIO_PC8;
}
 
void InitializeDiode2()
{
  AT91C_BASE_PIOC->PIO_PER = AT91C_PIO_PC29;
  AT91C_BASE_PIOC->PIO_OER = AT91C_PIO_PC29;
}
 
void TurnOnDiode1()
{
   AT91C_BASE_PIOB->PIO_CODR = AT91C_PIO_PC8;
}
 
void TurnOffDiode1()
{
   AT91C_BASE_PIOB->PIO_SODR = AT91C_PIO_PC8;
}
 
void TurnOnDiode2()
{
  AT91C_BASE_PIOC->PIO_CODR = AT91C_PIO_PC29;
}
 
void TurnOffDiode2()
{
   AT91C_BASE_PIOC->PIO_SODR = AT91C_PIO_PC29;
}
 
void InitializeAndEnablePushButtons()
{
  AT91C_BASE_PIOC->PIO_PER = AT91C_PIO_PC5;
  AT91C_BASE_PIOC->PIO_ODR = AT91C_PIO_PC5;
  AT91C_BASE_PIOC->PIO_PPUER = AT91C_PIO_PC5;
 
  AT91C_BASE_PIOC->PIO_PER = AT91C_PIO_PC4;
  AT91C_BASE_PIOC->PIO_ODR = AT91C_PIO_PC4;
  AT91C_BASE_PIOC->PIO_PPUER = AT91C_PIO_PC4;
}
 
void InitializeDiodesAndButtons()
{
  InitializeDiode1();
  InitializeDiode2();
  TurnOffDiode1();
  TurnOffDiode2();
  InitializeAndEnablePushButtons();
}
 
void TurnOnPeripheralClock()
{
  AT91C_BASE_PMC->PMC_PCER = AT91C_PIO_PC4;
}

void ClearInterruptStatusRegister()
{
	AT91C_BASE_PIOC->PIO_ISR;	
}
 
void ButtonInterruptHandler(void)
{
	volatile unsigned int clearFlag = AT91C_BASE_PIOC->PIO_ISR;  
	if(clearFlag & (AT91C_PIO_PC5))
	{   
		TurnOnDiode1();
		TurnOnDiode2();
	}
	else if(clearFlag & (AT91C_PIO_PC4))
	{
		TurnOffDiode1();
		TurnOffDiode2();
	}	
	else
	{
		SpuriousCount++;
	}
	ClearInterruptStatusRegister();
}

void InitializeInterrupts()
{
	TurnOnPeripheralClock();
	AT91C_BASE_AIC->AIC_IDCR = 1 << AT91C_ID_PIOCDE;
	AT91C_BASE_AIC->AIC_SVR[AT91C_ID_PIOCDE] = (unsigned int) ButtonInterruptHandler; 
	AT91C_BASE_AIC->AIC_SMR[AT91C_ID_PIOCDE] = AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL | AT91C_AIC_PRIOR_HIGHEST;
	AT91C_BASE_AIC->AIC_ICCR = 1 << AT91C_ID_PIOCDE;
	ClearInterruptStatusRegister();
	AT91C_BASE_PIOC->PIO_IER = AT91C_PIO_PC5;
	AT91C_BASE_PIOC->PIO_IER = AT91C_PIO_PC4;
	AT91C_BASE_AIC->AIC_IECR = 1 << AT91C_ID_PIOCDE;
}
