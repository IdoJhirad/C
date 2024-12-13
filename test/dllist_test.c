#include <stdio.h>/*printf*/
#include <string.h>/*strcat*/

#include "dllist.h"


char buffer[200];

void AddFailTest(char *ptr)
{
	strcat(buffer , ptr);
}

int IsEQual1( const void *data, const void *param)
{
	return *(int*)data == *(int*)param;
}

int IsMatch( const void *data, const   void *param)
{	
	int a = *(int *)data;
	int b = *(int *)param;
	return (a == b);
}


int Sum( void *data,  void *param)
{
	return *(int*)data += *(int*)param;
}

int TestCreateAndDestroy()
{
	dllist_t *list = DllistCreate();
	if(NULL == list)
	{
		AddFailTest("TestCreateAndDestroy faild\n");
		return 1;
	}
	DllistDestroy(list);
	return 0;
}
int TestInsertAndEndAndGetData()
{
	dllist_iter_t node = NULL;
	int data1 = 50;
	dllist_t *list = DllistCreate();
	if(NULL == list)
	{
		AddFailTest("TestCreateAndDestroy in insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistInsertBefore(list, &data1,DllistGetEnd(list));
	if(NULL == node)
	{
		AddFailTest("insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	if( 50 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Get data or insert faild");
		DllistDestroy(list);
		return 1;
	}
	DllistDestroy(list);
	return 0;
}
int TestInsertBeforeAndRemove()
{
	dllist_iter_t node = NULL;
	int data1 = 50;
	int data2 = 620;
	dllist_t *list = DllistCreate();
	if(NULL == list)
	{
		AddFailTest("TestCreateAndDestroy in insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistInsertBefore(list, &data1,DllistGetEnd(list));
	if(NULL == node)
	{
		AddFailTest("insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	if( 50 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Get data or insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistNext(node);
	node = DllistInsertBefore(list, &data2, node);
	if( 620 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Get data or insert faild2\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistPrev(node);
	if( 50 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Get data or insert faild3\n");
		DllistDestroy(list);
		return 1;
	}
	/*remove head*/
	node = DllistRemove(node);
	if( 620 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Get data or insert faild3\n");
		DllistDestroy(list);
		return 1;
	}
	DllistDestroy(list);
	return 0;
}

int TestPopPush()
{
	dllist_iter_t node = NULL;
	int data1 = 50;
	int data2 = 620;
	int data3 = 535;
	int data4 = 1;
	dllist_t *list = DllistCreate();
	if(NULL == list)
	{
		AddFailTest("TestCreateAndDestroy in insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistInsertBefore(list, &data1,DllistGetEnd(list));
	if(NULL == node)
	{
		AddFailTest("insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	if( 50 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Get data or insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistNext(node);
	node = DllistInsertBefore(list, &data2, node);
	if( 620 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Get data or insert faild2\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistNext(node);
	node = DllistInsertBefore(list, &data3, node);
	if( 535 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Get data or insert faild2\n");
		DllistDestroy(list);
		return 1;
	}
	
	if( 50 != *(int *)DllistPopFront(list))
	{	
		AddFailTest("Pop front faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistPushFront(list, &data4);
	node = DllistGetBegin(list);
	if( 1 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Push faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistPushBack(list, &data1);
	node = DllistGetEnd(list);
	node = DllistPrev(node);
	if( 50 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Push back faild\n");
		DllistDestroy(list);
		return 1;
	}
	if( 50 != *(int *)DllistPopBack(list))
	{	
		AddFailTest("pop back faild\n");
		DllistDestroy(list);
		return 1;
	}
	DllistDestroy(list);
	return 0;
}

int TestFindAndsize()
{
	dllist_iter_t node = NULL;
	int data1 = 50;
	int data2 = 620;
	int data3 = 535;
	int data4 = 1;
	dllist_t *list = DllistCreate();
	if(NULL == list)
	{
		AddFailTest("TestCreateAndDestroy in insert faild\n");
		DllistDestroy(list);
		return 1;
	}
	if(0 == DllistIsEmpty(list))
	{
		AddFailTest("Is Empty faild\n");
		DllistDestroy(list);
		return 1;
	}
	if(0 != DllistSize(list))
	{
		AddFailTest("DllSize faild\n");
		DllistDestroy(list);
		return 1;
	}
	
	node = DllistInsertBefore(list, &data1,DllistGetEnd(list));
	if(1 != DllistSize(list))
	{
		AddFailTest("DllSize faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistNext(node);
	node = DllistInsertBefore(list, &data2, node);
	if(2 != DllistSize(list))
	{
		AddFailTest("DllSize faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistNext(node);
	node = DllistInsertBefore(list, &data3, node);
	if(3 != DllistSize(list))
	{
		AddFailTest("DllSize faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistRemove(node);
	if(2 != DllistSize(list))
	{
		AddFailTest("DllSize faild\n");
		DllistDestroy(list);
		return 1;
	}
	node = DllistPrev(node);
	node = DllistRemove(node);
	if(1 != DllistSize(list))
	{
		AddFailTest("DllSize faild\n");
		DllistDestroy(list);
		return 1;
	}	
	node = DllistPushFront(list, &data4);
	node = DllistGetBegin(list);
	if(2 != DllistSize(list))
	{
		AddFailTest("DllSize faild\n");
		DllistDestroy(list);
		return 1;
	}	
	node = DllistPushBack(list, &data1);
	if(3 != DllistSize(list))
	{
		AddFailTest("DllSize faild\n");
		DllistDestroy(list);
		return 1;
	}	
	
	node = DllistFind(&data1 , DllistGetBegin(list), DllistGetEnd(list), IsMatch);
	if( 50 != *(int *)DllistGetData(node))
	{	
		AddFailTest("Push back faild\n");
		DllistDestroy(list);
		return 1;
	}
	DllistDestroy(list);

	return 0;
}

int TestDllistSplice()
{


	dllist_iter_t to = NULL;
	dllist_iter_t from = NULL;
	int data1 = 50;
	int data2 = 620;
	int data3 = 535;
	int data4 = 1;
	dllist_t *list = DllistCreate();
	dllist_t *list2 = DllistCreate();

	DllistPushFront(list, &data1);
	DllistPushFront(list, &data2);	
	DllistPushFront(list, &data3);
	DllistPushFront(list, &data4);

	DllistPushFront(list2, &data4);
	DllistPushFront(list2, &data1);
	DllistPushFront(list2, &data2);	
	DllistPushFront(list2, &data3);
	DllistPushFront(list2, &data4);

	/*data 4 suppusd to exist only once*/

	from = DllistGetBegin(list2);
	from = DllistNext(from); 
	to = DllistGetEnd(list2); 
	to = DllistPrev(to); 
	to = DllistPrev(to); 

	DllistSplice(DllistGetBegin(list), from, to);


    if (3 != DllistSize(list2))
    {
        AddFailTest("DllistSplice failed: list2 size is incorrect\n");
        DllistDestroy(list2);
        DllistDestroy(list);
        return 1;
    }


    if (6 != DllistSize(list))
    {
        AddFailTest("DllistSplice failed: list size is incorrect\n");
        DllistDestroy(list2);
        DllistDestroy(list);
        return 1;
    }

    DllistDestroy(list);
    DllistDestroy(list2);

    return 0;
}


int TestForEach()
{
	dllist_t *list = DllistCreate();
	int status = 0;
	int num = 1;
	int data = 1;
	dllist_iter_t node = NULL;
	node = DllistInsertBefore(list, &data, DllistGetEnd(list));
	DllistInsertBefore(list, &data, node);
	DllistInsertBefore(list, &data, node);
	DllistInsertBefore(list, &data, node);
	/*size 4 full with data 1*/
	status = DllistForEach(DllistGetBegin(list) , DllistGetEnd(list),  Sum, &num);
	if(0 == status )
	{
		AddFailTest("for each faild\n");
		DllistDestroy(list);
	}
	node = DllistGetBegin(list);
	if( 5 != *(int *)DllistGetData(node))
	{	
		AddFailTest("for each2 faild\n");
		DllistDestroy(list);
		return 1;
	}
	DllistDestroy(list);
	return 0; 
}

int TestIsSameIter()
{
	dllist_t *list = NULL;
	dllist_iter_t node1 = NULL;
	dllist_iter_t node2 = NULL;
	int arr[4] = {1, 2, 3, 4};
	

	list = DllistCreate();
	node1 = DllistGetBegin(list);
	node1 = DllistInsertBefore(list, arr, node1);
	node1 = DllistInsertBefore(list, arr+1, node1);
	node1 = DllistNext(node1);
	node1 = DllistInsertBefore(list, arr+2, node1);
	
	node1 = DllistGetBegin(list);
	node2 = DllistGetBegin(list);
	
	if (!DllistIsSameIter(node1, node2))
	{
		AddFailTest("TestIsSameIter\n");
		DllistDestroy(list);
		return 1;
	}
	
	node2 = DllistNext(node2);
	
	if (DllistIsSameIter(node1, node2))
	{
		AddFailTest("TestIsSameIter\n");
		DllistDestroy(list);
		return 1;
	}
	
	DllistDestroy(list);
	return 0;
}



int TestMultiFind()
{
	dllist_t *list = DllistCreate();
	dllist_t *output = DllistCreate();
	int status = 0;
	int data2 = 2;
	int data = 1;
	
	dllist_iter_t node = NULL;
	node = DllistInsertBefore(list, &data, DllistGetEnd(list));
	DllistInsertBefore(list, &data, node);
	DllistInsertBefore(list, &data, node);
	/* 1 1 1*/
	DllistInsertBefore(list, &data2, node);
	DllistInsertBefore(list, &data2, node);
	DllistInsertBefore(list, &data2, node);
	/* 222 111*/
	status =DllistMultiFind( DllistGetBegin(list), DllistGetEnd(list),IsEQual1, &data,output);
	if(3 != status)
	{
		AddFailTest("DllistMultiFind\n");
		DllistDestroy(list);
			DllistDestroy(output);
		return 1;
	}
	node = DllistGetBegin(output);
	if (1  !=*(int *)DllistGetData(node))
	{
		AddFailTest("DllistMultiFind 2\n");
		DllistDestroy(output);
		DllistDestroy(list);
		return 1;
	}
	DllistDestroy(output);
	DllistDestroy(list);
	return 0;
}

int main()
{
	int test_index = 0;
	test_index += TestCreateAndDestroy();
	printf("CreateAndDestroy tested\n");
	test_index +=TestInsertAndEndAndGetData();
	printf("Insert and get data tested\n");
	test_index += TestInsertBeforeAndRemove();
	printf("Insert and Before and Remove tested\n");
	test_index += TestPopPush();
	printf("PopPUSe tested\n");
	test_index += TestFindAndsize();
	printf("size and is empty and find  tested \n");
	test_index += TestDllistSplice();
	printf("TestDllistSplice  tested \n");
	test_index += TestForEach();
	printf("TestForEach  tested \n");
	test_index += TestIsSameIter();
	printf("TestIsSameIter  tested \n");
	test_index += TestMultiFind();
	printf("TestMultiFind  tested \n");
	if(test_index)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, test_index, 9, buffer);
		return test_index;

	}	
	printf("All test done \n");
	return 0;
}
