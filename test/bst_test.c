#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "bst.h"

#define TESTNUM 4
int TestInsertAndSize();
int TestCreatAndDystroy();
int TestInsertAndForEach();
int TestRemove();
int TestIsEmpty();
int TestFind();
static char failed_tests_print[200] = {'\0'};

void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}
int PrintNode(void *data, void *param)
{	
	(void)param;
	printf("%d ->", *(int *)data);

	return 0;
}

int Compare(const void *data,const void *param)
{	
	assert(data);
	assert(param);
	
	return (*(int *)data - *(int *)param);
}



int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestCreatAndDystroy();
	printf("Tested Creat And Destroy\n");
	failed_tests_num +=TestInsertAndSize();
	printf("Tested InsertAndSize\n");
	failed_tests_num += TestIsEmpty();
	printf("Tested IsEmpty\n");
	failed_tests_num +=TestInsertAndForEach ();
	printf("Tested InsertAndForEach\n");
	failed_tests_num +=TestRemove();
	printf("Tested Remove\n");
	failed_tests_num +=TestFind();
	printf("Tested find\n");
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

	bst_t *bst = BSTCreate(Compare);
	if(!bst)
	{
		AddFailedTest("create failed");
		return 1;
	}
	
	BSTDestroy(bst);
	return 0;
}

int TestInsertAndSize()
{
	int arr[]= {8,3,1,6,4,7,10,14,13};

	bst_t *bst = BSTCreate(Compare);
	if(!bst)
	{
		AddFailedTest("create failed");
		return 1;
	}
	if(BSTSize(bst))
	{
		AddFailedTest("size  failed");
		BSTDestroy(bst);
		return 1;
	}
	BSTInsert(bst, arr);
	if(1 != BSTSize(bst))
	{
		AddFailedTest("size OR INSERT  failed2\n");
		BSTDestroy(bst);
		return 1;
	}
	BSTInsert(bst, (arr+1));
	if(2 != BSTSize(bst))
	{
		AddFailedTest("size OR INSERT  failed3\n");
		BSTDestroy(bst);
		return 1;
	}
	
	BSTDestroy(bst);
	return 0;
}
int TestIsEmpty()
{
	int arr[]= {8,3,1,6,4,7,10,14,13};

	bst_t *bst = BSTCreate(Compare);
	if(!bst)
	{
		AddFailedTest("create failed");
		return 1;
	}
	if(!BSTIsEmpty(bst))
	{
		AddFailedTest("IsEmpty faild");
		BSTDestroy(bst);
		return 1;
	}
	BSTInsert(bst, (arr+1));
	if(1 != BSTSize(bst))
	{
		AddFailedTest("size OR INSERT  failed\n");
		BSTDestroy(bst);
		return 1;
	}
	if(1 == BSTIsEmpty(bst))
	{
		AddFailedTest("IsEmpty faild");
		BSTDestroy(bst);
		return 1;
	}
	BSTDestroy(bst);
	return 0;
	
}


int TestInsertAndForEach()
{
	int arr[]= {8,3,1,6,4,7,10,14,13};
	size_t i =1;
	bst_iter_t runner = NULL;
	bst_t *bst = BSTCreate(Compare);
	if(!bst)
	{
		AddFailedTest("create failed");
		return 1;
	}
	runner = BSTInsert(bst ,(arr));
	if(arr[0] != *(int *)BSTGetData(runner))
	{
		AddFailedTest("Get Data or insert faild");
		BSTDestroy(bst);
		return 1;
	}

	while(i<9)
	{
		runner = BSTInsert(bst ,(arr+i));
		if(arr[i] != *(int *)BSTGetData(runner))
		{
			AddFailedTest("Get Data or insert faild");
			BSTDestroy(bst);
			return 1;
		}
		++i;
	}
	printf("\nshpuld print list with  1 3 4 6 7 8 10 13 14 \n");
	BSTForEach(bst, PrintNode, NULL);
	printf("\n");
	
	if(9 != BSTSize(bst))
	{
		AddFailedTest("size failed\n");
		BSTDestroy(bst);
		return 1;
	}
	BSTDestroy(bst);
	return 0;
}


int TestRemove()
{
	int arr[]= {8,3,1,6,4,7,10,14,13};
	size_t i =1;
	bst_iter_t runner = NULL;
	bst_t *bst = BSTCreate(Compare);
	void *data = NULL;
	if(!bst)
	{
		AddFailedTest("create failed");
		return 1;
	}
	runner = BSTInsert(bst ,(arr));
	if(arr[0] != *(int *)BSTGetData(runner))
	{
		AddFailedTest("Get Data or insert faild");
		BSTDestroy(bst);
		return 1;
	}

	while(i<9)
	{
		runner = BSTInsert(bst ,(arr+i));
		if(arr[i] != *(int *)BSTGetData(runner))
		{
			AddFailedTest("Get Data or insert faild");
			BSTDestroy(bst);
			return 1;
		}
		++i;
	}
	runner = BSTEnd(bst);
	runner = BSTPrev(runner);
	if(14 != *(int *)BSTGetData(runner))
	{
		AddFailedTest("Prev faild");
		BSTDestroy(bst);
		return 1;
	}
	data = BSTRemove(runner);
	if(14 != (*(int*)data))
	{
			AddFailedTest("remove faild1");
			BSTDestroy(bst);
			return 1;
	}
	runner =  BSTBegin(bst);
	runner =  BSTNext(runner);
	data = BSTRemove(runner);
	if(3!= (*(int*)data))
	{
			AddFailedTest("remove faild2");
			BSTDestroy(bst);
			return 1;
	}
	BSTForEach(bst, PrintNode, NULL);
	runner =  BSTBegin(bst);
	runner =  BSTNext(runner);
	runner =  BSTNext(runner);	
	runner =  BSTNext(runner);
	data = BSTRemove(runner);
	if(7!= (*(int*)data))
	{
			AddFailedTest("remove faild3");
			BSTDestroy(bst);
			return 1;
	}
	if(6 != BSTSize(bst))
	{
		AddFailedTest("size or remove failed\n");
		BSTDestroy(bst);
		return 1;
	}
	runner =  BSTBegin(bst);
	data = BSTRemove(runner);
	
	printf("after root remove\n");
	BSTForEach(bst, PrintNode, NULL);
	BSTDestroy(bst);
	return 0;
}


int TestFind()
{
	int arr[]= {8,3,1,6,4,7,10,14,13};
	size_t i =1;
	
	bst_iter_t runner = NULL;
	bst_t *bst = BSTCreate(Compare);
	if(!bst)
	{
		AddFailedTest("create failed");
		return 1;
	}
	runner = BSTInsert(bst ,(arr));
	if(arr[0] != *(int *)BSTGetData(runner))
	{
		AddFailedTest("Get Data or insert faild");
		BSTDestroy(bst);
		return 1;
	}

	while(i<9)
	{
		runner = BSTInsert(bst ,(arr+i));
		if(arr[i] != *(int *)BSTGetData(runner))
		{
			AddFailedTest("Get Data or insert faild");
			BSTDestroy(bst);
			return 1;
		}
		++i;
	}
	runner = BSTFind(bst, arr+3);
	i = 0;
	while(i<9)
	{
		runner = BSTFind(bst, arr+i);
		if(arr[i] != *(int *)BSTGetData(runner))
		{
			AddFailedTest("find faild");
			BSTDestroy(bst);
			return 1;
		}
			AddFailedTest("find faild");
		++i;
	}
	BSTDestroy(bst);
	
	return 0;
	
}


