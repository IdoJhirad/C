#include <stdio.h>/*printf*/

#include "queue.h"

/*
queue_t *QCreate(void);
void QDestroy(queue_t *queue);

int QEnqueue(queue_t *queue, void *data);
void QDequeue(queue_t *queue);
size_t QSize(const queue_t *queue);
void *QPeek(const queue_t *queue);
int QIsEmpty(const queue_t *queue);
void QAppend(queue_t *dest_queue, queque_t *src_queue);

*/

void TestQAppend()
{
	queue_t *queue = QCreate();
	queue_t *queue2 = QCreate();
	int num = 10;
	int num2 = 20;
	QEnqueue(queue2, &num2);

	QEnqueue(queue, &num);
	QEnqueue(queue, &num);
	QEnqueue(queue2, &num2);
	QAppend(queue2,queue);
	if(4 == QSize(queue2))
	{
		printf("append sucseed\n");
	}
	else
	{
		printf("append not sucseed\n;");
	}
	QDestroy(queue);
	QDestroy(queue2);	

}

void TestQPeekAndEmpty()
{
	queue_t *queue = QCreate();
	int num = 10;
	int *ptr = NULL;
	int index= 0;
	
	int in =QEnqueue(queue, &num);
	if(0 == in)
	{
		printf("add sucseed\n");
	}
	ptr =(int*) QPeek(queue);
	if(10== *ptr)
	{
		printf("peek sucseed\n");
	}
	else 
	{
		printf("peek faild\n");
	}
	QDequeue(queue);
	index = QIsEmpty(queue);
	if(1 == index)
	{
		printf("is empty sucseed\n");
	}
	else
	{	
		printf("is empty faild\n");
	}
	QDestroy(queue);
		
}
void TestQDequeue()
{
	queue_t *queue = QCreate();
	int num = 10;
	size_t size = 0;
	int in= QEnqueue(queue, &num);
	if(0 == in)
	{
		printf("add sucseed\n");
	}

	in= QEnqueue(queue, &num);
	if(0 == in)
	{
		printf("add sucseed\n");
	}
	size = QSize(queue);	
	printf("size is : %ld\n", size);
	
	QDequeue(queue);
	size = QSize(queue);	
	if(1 == size)
	{
		printf("QDequeue sucseed\n");
	}
	else
	{
		printf("QDequeue faild\n");	
	}
	QDestroy(queue);	
}
void TestCreate()
{
	queue_t *queue = QCreate();
	QDestroy(queue);	
	printf("test create and destroy sucseed\n");
}

void TestAdd()
{
	queue_t *queue = QCreate();
	int num = 10;
	size_t size = 0;
	int in= QEnqueue(queue, &num);
	if(0 == in)
	{
		printf("add sucseed\n");
	}

	in= QEnqueue(queue, &num);
	if(0 == in)
	{
		printf("add sucseed\n");
	}
	size = QSize(queue);	
	printf("size is : %ld\n", size);
	QDestroy(queue);	
}
int main()
{	
	TestCreate();
	TestAdd();
	TestQDequeue();
	TestQPeekAndEmpty();
	TestQAppend();
	return 0;
}
