#include "FIFO.h"

int FifoPut(char input)
{
	if((FIFO.head == BUFFERSIZE -1 && FIFO.tail == 0) || (FIFO.tail-FIFO.head == 1))
		return 0;
	FIFO.data[FIFO.head++] = input;
	if(FIFO.head == BUFFERSIZE)
		FIFO.head = 0;
	return 1;
}

int FifoGet(char* output)
{
	if(FIFO.head == FIFO.tail)
		return 0;
	*output = FIFO.data[FIFO.tail++];
	if(FIFO.tail == BUFFERSIZE)
		FIFO.tail = 0;
	return 1;
}

void BufferInit()
{
	FIFO.head = 0;
	FIFO.tail = FIFO.head;
}
