#define BUFFER_SIZE 10
#define ERROR -1
#define CORRECT 1

typedef struct FIFO 
{
	char buffer [BUFFER_SIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int number_of_elements;
}FIFO;

void FIFOInit (struct FIFO *Fifo);
void FIFOEmpty (struct FIFO *Fifo);
int FIFOPut (struct FIFO *Fifo, char Data);
int FIFOGet (struct FIFO *Fifo, char *Data);


