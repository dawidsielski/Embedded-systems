#define BUFFERSIZE 10

struct Buffer
{
	char data[BUFFERSIZE];
	unsigned int head;
	unsigned int tail;
}FIFO;

int FifoPut(char input);
int FifoGet(char* output);
void BufferInit();


