#include "FIFO.h"

void FIFOInit (struct FIFO *Fifo)
{
 	Fifo->head = 0;
 	Fifo->tail = 0;
 	Fifo->number_of_elements = 0;
}

void FIFOEmpty (struct FIFO *Fifo)
{
	Fifo->head = Fifo->tail;
	Fifo->number_of_elements = 0;
}

int FIFOPut (struct FIFO *Fifo, char Data)
{
	if (Fifo->number_of_elements == BUFFER_SIZE){
		return ERROR; 
	};
	
	Fifo->buffer[Fifo->head] = Data;
	Fifo->head = (Fifo->head + 1) % (BUFFER_SIZE);
	Fifo->number_of_elements++;
	return CORRECT;
}

int FIFOGet (struct FIFO *Fifo, char *Data)
{
	if (Fifo->number_of_elements == 0){
		return ERROR;
	}

	*Data = Fifo->buffer[Fifo->tail];
	Fifo->tail = (Fifo->tail + 1) % (BUFFER_SIZE);
	Fifo->number_of_elements--;
	return CORRECT;
}

