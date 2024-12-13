#include <stdio.h> /*printf*/
#include <stdlib.h> /*free*/
#include "sllist.h"

void TestAppend();
 
 
int isEqual(const void *data, void *param)
{	
	int a = *(int *)data;
	int b = *(int *)param;
	return (a == b);
}


int TestInsertAndGet()
{
	size_t test_data = 0;
	sllist_iter_t node_1;
	sllist_iter_t node_2;
	sllist_iter_t node_3;

	int return_v= 0;
	size_t size = 0;
	 
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 75;

	
	int set = 8;
	
	int element = 0;
	sllist_t *sllist = SllistCreate();
	if(NULL == sllist)
	{
		return 0;
	}
	printf("SllistCreate worked \n");
	++test_data;
	
	
	
		node_1 = SllistBegin(sllist);
		node_1 = SllistInsertBefore(sllist, &data1 , node_1 );
	element = *(int *)SllistGetData(SllistBegin(sllist));
	
	
	printf("\nget data output %d\n",element);
	if (*(int *)SllistGetData(SllistBegin(sllist)) == data1 )
	{
		printf("SllistInsertBefore and get data sucseed \n");
		++test_data;
	}
	else
	{
		printf("SllistInsertBefore failed for node 1\n");
	}
	
	node_2 = SllistInsertBefore(sllist, &data2 , node_1 );

	
	
	node_3 = SllistInsertBefore(sllist, &data3 , node_2 );

	/*SllistBegin*/
	if (SllistBegin(sllist) == node_1 )
	{
		printf("\nSllistBegin work for node 1\n\n");
		++test_data;
	}
	else
	{
		printf("\nSllistBegin failed for node 1\n\n");
	}
	
	/*next*/
	
	/*printf("\nnext test SllistGetData \n");*/
	node_1 = SllistBegin(sllist);

	if(*(int *)SllistGetData(node_2) == data3)
	{
		printf("\ntest for next and SllistGetData worked \n");
	}
		element = *(int *)SllistGetData(node_1);
	printf("get data output %d\nfirst iterator \n",element);
	
	node_1 = SllistNext(node_1);
	element = *(int *)SllistGetData(node_1);
	printf("get data output %d \nsecound iterator \n",element);
	
	node_1 = SllistNext(node_1);
	element = *(int *)SllistGetData(node_1);
	printf("get data output %d \nthird iterator \n",element);

	/*in the end remove and its emptty*/
	printf("\n remove\n");
	
	node_1 = SllistBegin(sllist);
	
	node_1 = SllistRemove(node_1);
	node_1 = SllistRemove(node_1);
	node_1 = SllistRemove(node_1);
	
	
	
	if (SllistIsEmpty(sllist))
	{
		printf("\nSllistIsEmpty and SllistRemove  works its empty \n\n");
		++test_data;
	}
	else
	{
		printf("\n SllistIsEmpty and SllistRemove  faild \n");
	}
	
	
	data1 = 1;
	data2 = 2;
	data3 = 3;
	data4 = 2;

	node_3 = SllistBegin(sllist);
	
	node_3 = SllistInsertBefore(sllist, &data1 , node_3 );
	node_3 = SllistNext(node_3);
	node_3 = SllistInsertBefore(sllist, &data2 , node_3 );
	node_3 = SllistNext(node_3);
	node_3 = SllistInsertBefore(sllist, &data3 , node_3 );
	node_3 = SllistNext(node_3);
	node_3 = SllistInsertBefore(sllist, &data4 , node_3 );
	node_3 = SllistNext(node_3);
	
	
	/*printf("\n set data\n");*/
	/**************
	*************/
	node_3 = SllistBegin(sllist);
	node_3 = SllistSetData(node_3, &set);
	node_3 = SllistNext(node_3);
	node_3 = SllistNext(node_3);
	node_3 = SllistSetData(node_3, &set);
	if(*(int *)SllistGetData(node_1)== set)
	{
		printf("\nSllistSetData sucseed\n");	
	}
	else
	{
		printf("\nSllistSetData faild\n");	
	}
	
	node_3 = SllistNext(node_3);
	
	node_3 = SllistBegin(sllist);

	while( SllistEnd(sllist)!= node_3 )
	{
		printf("%d",*(int *)SllistGetData(node_3));
		node_3 = SllistNext(node_3);
	}
		printf("\n");
	/*****************************************/
	node_3 = SllistBegin(sllist);
	node_3 = SllistNext(node_3);
	node_2 = SllistNext(node_3);
	node_3 = SllistNext(node_2);

	
	return_v =  SllistIterIsEqual(node_2, node_3);
	if(1 == return_v)
	{
		printf("\nare equal\n");
		++test_data;
	}
	else
	{
		printf("\nare notequal\n");
		++test_data;
	}
	
	/* starat of find test*/
	/*printf("\nstarat of find test\n");*/
	node_3 = SllistNext(node_3);
	node_3 = SllistInsertBefore(sllist, &data5 , node_3);
	
	
	node_2 = SllistBegin(sllist);
	node_2 = SllistFind(&data5,node_2,SllistEnd(sllist),&isEqual);
	element = *(int *)SllistGetData(node_2);
	if(element==data5)
	{
		printf(" \nSllistFind sucseed\n");
	}
	else
	{
			printf(" \nSllistFind faild\n");
	}
	
	
	
	
	printf("\nsize test\n");
	size = SllistCount(sllist);
	
	printf("size = %ld\n", size);
	

	
	SllistDestroy(sllist);

	return 0;
}

void TestAppend()
{
	sllist_iter_t node_1 = NULL;
	sllist_iter_t node_2 = NULL;
	
	int data1=15;
	int data2=16;
	int data3=17;
	int data4 = 20;
	sllist_t *sllist = SllistCreate();
	sllist_t *sllist2 = SllistCreate();
	
	if(NULL == sllist)
	{
		return ;
	}
	if(NULL == sllist2)
	{
		return ;
	}
	node_1 = SllistBegin(sllist);
	node_1 = SllistInsertBefore(sllist, &data1 , node_1 );
	node_1 = SllistInsertBefore(sllist, &data4 , node_1 );

	
	node_2 = SllistBegin(sllist2);
	node_2 = SllistInsertBefore(sllist2, &data2 , node_2 );
	node_2 = SllistInsertBefore(sllist2, &data3 , node_2 );

	
	SllistAppend(sllist ,sllist2);
	
	SllistDestroy(sllist);
	SllistDestroy(sllist2);


	
}
void test_SllistAppend(void)
{
	sllist_t *list = SllistCreate();
	sllist_t *list2 = SllistCreate();
	int x = 5, y = 7, z = 6;
	sllist_iter_t iter = SllistBegin(list);
	sllist_iter_t iter2 = SllistBegin(list2);
	SllistInsertBefore(list, &x, iter);
	SllistInsertBefore(list, &y, iter);
	SllistInsertBefore(list2, &z, iter2);
	SllistAppend(list, list2);
    SllistDestroy(list);
}	



int main()
{
	TestInsertAndGet();
	/*TestAppend();*/
	/*test_SllistAppend();*/
	return 0;
}







