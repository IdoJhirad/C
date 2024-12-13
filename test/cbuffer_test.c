#include <stdio.h>/*printf*/
#include <string.h>/*strcat*/

#include "cbuffer.h"

#define NUMBER_OF_CASES 6

static int TestCreateAndDestroy();
 static int TestFreeSpace();
static int TestCBuffSize();
static int TestCBuffReadWrite();
static int TestCBuffIsEmpty();

static  char buffer[200];

void AddFailTest(char *ptr)
{
	strcat(buffer , ptr);
}

int main()
{	
	int test_index = 0;
	
	test_index += TestCreateAndDestroy();
	printf("TestCreateAndDestroy\n");
	test_index += TestFreeSpace();
	printf("TestFreeSpace\n");
	test_index += TestCBuffSize();
	printf("TestCBuffSize\n");
	test_index += TestCBuffReadWrite();
	printf("TestCBuffReadWrite\n");
	test_index += TestCBuffIsEmpty();
	printf("TestCBuffIsEmpty\n");
	if(test_index)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, test_index, 5, buffer);
		
		return test_index;

	}
	printf("all passed\n");
	
	return 0;
}



static int TestCreateAndDestroy()
{
	size_t capacity = 10;
	cbuffer_t *buffer= CBuffCreate(capacity);
	
	if(NULL == buffer)
	{
		AddFailTest("TestCreateAndDestroy faild\n");
		return 1;
	}
	CBuffDestroy(buffer);
	
	return 0;
}

static int TestFreeSpace()
{
	size_t capacity = 10;
	char *str = "abcdefg";
	char dest[30];

	cbuffer_t *buffer= CBuffCreate(capacity);
	CBuffWrite(buffer, str, 5);
	if(5 != CBuffFreeSpace(buffer))
	{
		AddFailTest("free space 1 faild \n");
		CBuffDestroy(buffer);
		return 1;
	}
	CBuffWrite(buffer, str, 3);
	if(2 != CBuffFreeSpace(buffer))
	{
		AddFailTest("free space 2 faild \n");
		CBuffDestroy(buffer);
		return 1;
	}
	CBuffWrite(buffer, str, 2);
	if(0 != CBuffFreeSpace(buffer))
	{
		AddFailTest("free space 3 faild \n");
		CBuffDestroy(buffer);
		return 1;
	}
	CBuffRead(buffer, dest, 2);
	if(2 != CBuffFreeSpace(buffer))
	{
		AddFailTest("free space 4 faild \n");
		CBuffDestroy(buffer);
		return 1;
	}
	CBuffDestroy(buffer);
	
	return 0;
}

static int TestCBuffSize()
{
	size_t capacity = 10;
	char *str = "abcdefg";

	cbuffer_t *buffer= CBuffCreate(capacity);
	if(CBuffSize(buffer) != 10)
	{
		AddFailTest("CBuffSize 1 faild \n");
		CBuffDestroy(buffer);
		return 1;
	}
	 CBuffWrite(buffer, str, 5);
	if(CBuffSize(buffer) != 10)
	{
		AddFailTest("free space 2 faild \n");
		CBuffDestroy(buffer);
		return 1;
	}
	CBuffDestroy(buffer);
	
	return 0;
}

static int TestCBuffReadWrite()
{
	size_t capacity = 10;
	char *str = "abcdefghijklmnop55555555555555555555555555";
	char dest[5];

	cbuffer_t *buffer= CBuffCreate(capacity);
	 CBuffWrite(buffer, str, 13);
	CBuffRead(buffer, dest, 5);
	if(0!= strncmp( dest , str+3, 5))
	{
		AddFailTest("CBuffReadandWrite 1 faild \n");
		CBuffDestroy(buffer);
		return 1;
	}	
	CBuffDestroy(buffer);
	
	return 0;
}
static int TestCBuffIsEmpty()
{	
	size_t capacity = 10;
	char *str = "abcdefghijklmnop";
	char dest[10];

	cbuffer_t *buffer= CBuffCreate(capacity);
	int is_empty = CBuffIsEmpty(buffer);
	if(1 != is_empty)
	{
		AddFailTest("is_empty 1 faild \n");
		CBuffDestroy(buffer);
		return 1;
	}
	 CBuffWrite(buffer, str, 10);
	is_empty = CBuffIsEmpty(buffer);
	if(0 != is_empty)
	{
		AddFailTest("is_empty 2 faild \n");
		CBuffDestroy(buffer);
		
		return 1;	
	}
	CBuffRead(buffer, dest, 10);
	is_empty = CBuffIsEmpty(buffer);
	if(1 != is_empty)
	{
		AddFailTest("is_empty 3 faild \n");
		CBuffDestroy(buffer);
		
		return 1;	
	}
	CBuffDestroy(buffer);
	
	return 0;
	
}



