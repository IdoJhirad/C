#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "heap.h"

#define TESTNUM 4

int TestCreatAndDystroy();
int TestPush();
int TestPop();
int TestRemove();
static char failed_tests_print[200] = {'\0'};


int Compare(const void *data,const void *param)
{	
	assert(data);
	assert(param);
	
	return (*(int *)data - *(int *)param);
}
int IsMatch(const void *data,const void *param)
{	
	assert(data);
	assert(param);
	
	return (*(int *)data == *(int *)param);
}
void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}
int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestCreatAndDystroy();
	printf("Tested Creat And Destroy\n");
	failed_tests_num +=TestPush();
	printf("Tested TestPush\n");
	failed_tests_num += TestPop();
	printf("Tested TestPop\n");
	failed_tests_num +=TestRemove ();
	printf("Tested TestRemove\n");
	/*failed_tests_num +=TestRemove();
	printf("Tested Remove\n");
	failed_tests_num +=TestFind();
	printf("Tested find\n");*/
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}

int TestCreatAndDystroy()
{

	heap_t *heap = HeapCreate(Compare);
	if(!heap)
	{
		AddFailedTest("create failed");
		return 1;
	}
	if( 0 != HeapSize(heap))
	{
		AddFailedTest("size failed");
		HeapDestroy(heap);
		return 1;
	}
	if(!HeapIsEmpty(heap))
	{	
		printf("%d\n",HeapIsEmpty(heap) );
		AddFailedTest("is empty failed");
		HeapDestroy(heap);
		return 1;
	}
	HeapDestroy(heap);
	return 0;	
}
	
int TestPush()
{
	int num = 0;
	int arr[8]={1,32,6,25,5,0,2,7};
	size_t i = 0;
	heap_t *heap = HeapCreate(Compare);
	if(!heap)
	{
		AddFailedTest("create failed");
		return 1;
	}
	if( 0 != HeapSize(heap))
	{
		AddFailedTest("size failed");
		HeapDestroy(heap);
		return 1;
	}
	if(!HeapIsEmpty(heap))
	{	
		printf("%d\n",HeapIsEmpty(heap) );
		AddFailedTest("is empty failed");
		HeapDestroy(heap);
		return 1;
	}
	for(;i < 8;++i)
	{
		HeapPush(heap , &arr[i]);
		if( i+1 != HeapSize(heap))
		{
			AddFailedTest("size failed");
			HeapDestroy(heap);
			return 1;
		}
		if(HeapIsEmpty(heap))
		{		
			printf("%d\n",HeapIsEmpty(heap) );
			AddFailedTest("is empty failed");
			HeapDestroy(heap);
			return 1;
		}
		/*printf("after heapify\n");
		PrintIntHeap(heap);*/
	}
	
	num = **(int**)HeapPeek(heap);
	printf(" %d \n\n", num);
	if( 0 != num)
	{		

		AddFailedTest(" HeapPeek failed\n");
		HeapDestroy(heap);
		return 1;
	}
	HeapDestroy(heap);
	return 0;	
}	

	
int TestPop()
{
	int num = 0;
	int arr[8]={1,32,6,25,5,0,2,7};
	size_t i = 0;
	heap_t *heap = HeapCreate(Compare);
	if(!heap)
	{
		AddFailedTest("create failed");
		return 1;
	}
	if( 0 != HeapSize(heap))
	{
		AddFailedTest("size failed");
		HeapDestroy(heap);
		return 1;
	}
	if(!HeapIsEmpty(heap))
	{	
		printf("%d\n",HeapIsEmpty(heap) );
		AddFailedTest("is empty failed");
		HeapDestroy(heap);
		return 1;
	}
	for(;i < 8;++i)
	{
		if( i != HeapSize(heap))
		{
			AddFailedTest("size failed");
			HeapDestroy(heap);
			return 1;
		}
		HeapPush(heap , &arr[i]);
	}

	if( 8 != HeapSize(heap))
	{
		AddFailedTest("size 1 failed");
		HeapDestroy(heap);
			return 1;
	}
	
	
	for(;i > 0;--i)
	{
		/*printf("%ld \n\n", i);*/
		if( i != HeapSize(heap))
		{
			AddFailedTest("size failed");
			HeapDestroy(heap);
			return 1;
		}

		printf("after heapify\n");
		PrintIntHeap(heap);

		HeapPop(heap);

	}

	HeapDestroy(heap);
	return 0;	
}	

int TestRemove()
{
	int num = 0;
	int arr[8]={1,32,6,25,5,0,2,7};
	size_t i = 0;
	int data = 0;
	heap_t *heap = HeapCreate(Compare);
	for(;i < 8;++i)
	{
		if( i != HeapSize(heap))
		{
			AddFailedTest("size failed");
			HeapDestroy(heap);
			return 1;
		}
		HeapPush(heap , &arr[i]);
	}

	if( 8 != HeapSize(heap))
	{
		AddFailedTest("size 1 failed");
		HeapDestroy(heap);
			return 1;
	}
	
	--i;
		
	for(;i > 1;--i)
	{
		printf("and arr is :%d \n", arr[i] );
		/*printf("remove\n");
		PrintIntHeap(heap);*/

		data = *(int*)HeapRemove(heap,IsMatch, &arr[i]);
		
		if(data != arr[i])
		{
		
			printf("data is:%d , and arr is :%d \n",data , arr[i] );
			AddFailedTest("removed failed\n");
			HeapDestroy(heap);
			return 1;
		}

	}

	HeapDestroy(heap);
	return 0;	
}	


