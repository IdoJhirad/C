#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "avl.h"

#define TESTNUM 4

static int TestCreatAndDystroy();
static int BabyTestForEmptyCountHightInsert();
static int TestRemove();
static int TestRemoveWithAVLHeight();

static char failed_tests_print[200] = {'\0'};

int PrintNode(void *data, void *param)
{	
	(void)param;
	printf("%d ->", *(int *)data);

	return 0;
}

void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
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
	failed_tests_num +=BabyTestForEmptyCountHightInsert();
	printf("Tested BabyTestForEmptyCountHightInsert\n");
	failed_tests_num += TestRemove();
	printf("Tested Remove\n");
	failed_tests_num +=TestRemoveWithAVLHeight();
	printf("Tested TestRemoveWithAVLHeight\n");
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

static int TestCreatAndDystroy()
{
	avl_t *avl = AVLCreate(Compare);
	if(!avl)
	{
		AddFailedTest("create faild");
		return 1;
	}
	
	if(!AVLIsEmpty(avl))
	{
		AddFailedTest("isEmpty faild");
		AVLDestroy(avl);
		return 1;
	}

	if(AVLCount(avl))
	{
		AddFailedTest("count faild\n");
		AVLDestroy(avl);
		return 1;
	}
	AVLDestroy(avl);
	
	return 0;
}

static int BabyTestForEmptyCountHightInsert()
{
	int arr[] = {15 ,20 ,30 ,74, 2, 5, 6, 25, 0, 80};
	avl_t *avl = AVLCreate(Compare);
	size_t index = 0;
	int num = 5;
	if(!avl)
	{
		AddFailedTest("create faild");
		return 1;
	}
	
	if( AVLHeight(avl))
	{
		AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert 1\n");
		AVLDestroy(avl);
		return 1;
	}


	for(; index < 9; ++index)
	{
		if(AVLCount(avl) != index)
		{
			AddFailedTest("Count faild to keep up \n");
			printf("count is %ld, index is %ld \n",index, AVLCount(avl));
			printf("the itration that faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
		num = AVLInsert(avl, arr + index);
		/*printf("%d \n", num);*/
		if(0 !=num )
		{
			AddFailedTest("insert statud return faild \n");
			printf("the itration thai faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
		/*printf( "\n  the height in the %ld itaretion is :%ld and the data is %d\n ", index , AVLHeight(avl)  , *(arr+index));*/
		
	}
	
	if( 4 != AVLHeight(avl))
	{
			AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert  2\n");
			AVLDestroy(avl);
			return 1;
	}
	num = AVLInsert(avl, arr + index);
	if(0 !=num )
	{
		AddFailedTest("insert statud return faild \n");
		printf("the itration thai faild is %ld\n", index);
		AVLDestroy(avl);
		return 1;
	}	
	printf("%ld \n" , AVLHeight(avl));
	if( 5 != AVLHeight(avl))
	{
			AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert 3\n");
			AVLDestroy(avl);
			return 1;
	}
	/*printf("%ld \n" , index);*/
	-- index;
	
	/*printf("%ld \n" , index);*/
	for(; index > 0 ; --index)
	{
		if( *(arr+index) != *(int*)AVLFind(avl ,(arr + index)))
		{
			AddFailedTest("find faild\n");
			AVLDestroy(avl);
			return 1;
		}
	}
	AVLDestroy(avl);
	
	return 0;
}


static int TestRemove()
{
	int arr[] = {15 ,20 ,30 ,74, 2, 5, 6, 25, 0, 80, 27 ,24};
	int arr_test2[] = {15 ,20 ,3,12, 21 ,30 ,74, 2, 5, -5 ,62,6,-4, 25, 0, 80};
	avl_t *avl = AVLCreate(Compare);
	size_t index = 0;
	int num = 5;
	if(!avl)
	{
		AddFailedTest("create faild");
		return 1;
	}
	
	if(AVLHeight(avl))
	{
		AddFailedTest("hight faild\n");
		AVLDestroy(avl);
		return 1;
	}

	
	for(; index < 11; ++index)
	{
		
		num = AVLInsert(avl, arr + index);
		if(0 !=num )
		{
			AddFailedTest("insert statud return faild in Remove \n");
			printf("the itration thai faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
	}	
	
	printf("/n before remove 80\n ");
	AVLForEach(avl ,PrintNode , &num );
		printf( "\n count : %ld\n ", AVLCount(avl));
	/*start with leaf*/
	/*remove right leaf 80*/
	printf("\n remove 80\n ");
	AVLRemove(avl, arr+ 9 );
	printf("\n after remove 80\n ");
	AVLForEach(avl ,PrintNode , &num );
	if( NULL != AVLFind(avl ,(arr + 9)))
	{
		AddFailedTest("find  or remove faild 1\n");
		AVLDestroy(avl);
		return 1;
	}
			printf( "\n count : %ld\n ", AVLCount(avl));
	printf("\n ");
	/*remove right leaf 74*/
	printf("\n after remove 74\n ");
	AVLRemove(avl, arr+ 3 );
	
	AVLForEach(avl ,PrintNode , &num );
	if( NULL != AVLFind(avl ,(arr + 3)))
	{
		AddFailedTest("find  or remove faild 2\n");
		AVLDestroy(avl);
		return 1;
	}
			printf( "\n count : %ld\n ", AVLCount(avl));
	/*remove 2 with left child*/ 
	
	printf("\n ");
	AVLRemove(avl, arr+ 4 ); 
	
	printf("\n after remove 2\n ");
	AVLForEach(avl ,PrintNode , &num );
	
	printf( "\n count : %ld\n ", AVLCount(avl));
	if( NULL != AVLFind(avl ,(arr + 4)))
	{
		AddFailedTest("find  or remove faild 3\n");
		AVLDestroy(avl);
		return 1;
	}
	/*check if size chenge*/
	if(AVLCount(avl) != 8)
	{
		AddFailedTest("Count with remove faild to keep up \n");
		printf("count is %ld, \n",AVLCount(avl));
		AVLDestroy(avl);
		return 1;
	}
	printf("\n ");
	
	
	/*remove  with right child data to remove = 0 (right leaf)*/
	AVLRemove(avl, arr+ 8 ); 
	printf("\n after remove 0\n ");
	AVLForEach(avl ,PrintNode , &num );
	printf( "\n count after 0 removed  should be  7 %ld\n ", AVLCount(avl));
	if( NULL != AVLFind(avl ,(arr + 8)))
	{
		AddFailedTest("find  or remove faild 4\n");
		AVLDestroy(avl);
		return 1;
	}
	printf("\n ");	
	/*remove root 15*/
	AVLRemove(avl, arr ); 
	AVLForEach(avl ,PrintNode , &num );
	printf( "\n count : %ld\n ", AVLCount(avl));
	if( NULL != AVLFind(avl ,(arr)))
	{
		AddFailedTest("find  or remove faild 5 \n");
		AVLDestroy(avl);
		return 1;
	}
	
	if(AVLCount(avl) != 6)
	{
		AddFailedTest("Count with remove faild to keep up \n");
		printf("count is %ld, \n",AVLCount(avl));
		AVLDestroy(avl);
		return 1;
	}
	AVLDestroy(avl);
	
	/*remove test 2*/
	

	avl = AVLCreate(Compare);
	index = 0;
	num = 5;
	if(!avl)
	{
		AddFailedTest("create faild in remove test 2");
		return 1;
	}
	
	for(; index < 16; ++index)
	{

		if(AVLCount(avl) != index)
		{
			AddFailedTest("Count faild to keep up \n");
			printf("count is %ld, index is %ld \n",index, AVLCount(avl));
			printf("the itration that faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
		num = AVLInsert(avl, arr_test2 + index);

		if(0 !=num )
		{
			AddFailedTest("insert statud return faild \n");
			printf("the itration thai faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
		
	}

	for(index = 0 ; index < 16 ; ++index)
	{
		AVLRemove(avl, arr_test2 + index );
		if(AVLCount(avl) != 15 - index)
		{
			AddFailedTest("Count faild to keep up \n");
			printf("count is %ld, index is %ld \n",index, AVLCount(avl));
			printf("the itration that faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
	}
	AVLDestroy(avl);

	return 0;
}



static int TestRemoveWithAVLHeight()
{
	int arr_test2[] = {15 ,20 ,3,12, 21 ,30 ,74, 2, 5, 4 ,62,6, 7, 25, 0, 80};
	avl_t *avl = AVLCreate(Compare);
	size_t index = 0;
	int num = 5;
	if(!avl)
	{
		AddFailedTest("create faild");
		return 1;
	}
	
	if(AVLHeight(avl))
	{
		AddFailedTest("hight faild\n");
		AVLDestroy(avl);
		return 1;
	}
	for(; index < 16; ++index)
	{

		if(AVLCount(avl) != index)
		{
			AddFailedTest("Count faild to keep up \n");
			printf("count is %ld, index is %ld \n",index, AVLCount(avl));
			printf("the itration that faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
		num = AVLInsert(avl, arr_test2 + index);
		/*printf( "\n  the height in the %ld itaretion is %ld\n ",index , AVLHeight(avl));*/
		if(0 !=num )
		{
			AddFailedTest("insert statud return faild \n");
			printf("the itration thai faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
	}	
	if(6 != AVLHeight(avl))
	{
		AddFailedTest("hight faild in insert\n");
		AVLDestroy(avl);
		return 1;
	}
	
	/*remove the last lever 62 80 7*/
	AVLRemove(avl, arr_test2 + 15 );
	AVLRemove(avl, arr_test2 + 12 );
	AVLRemove(avl, arr_test2 + 10 );
	if(AVLCount(avl) != 13)
	{
		AddFailedTest("Count faild in remove test remove 2 \n");

		AVLDestroy(avl);
		return 1;
	}
	if(5 != AVLHeight(avl))
	{
		AddFailedTest("hight faild \n");
		AVLDestroy(avl);
		return 1;
	}
	/*remove  layer 6 25 74  should not effect on height*/
	AVLRemove(avl, arr_test2 + 11 );
	AVLRemove(avl, arr_test2 + 13 );
	AVLRemove(avl, arr_test2 + 6 );
	AVLRemove(avl, arr_test2 + 9);
	if(AVLCount(avl) != 9)
	{
		AddFailedTest("Count faild in remove test remove 2 \n");

		AVLDestroy(avl);
		return 1;
	}

	if(4 != AVLHeight(avl))
	{
		AddFailedTest("hight faild in remove 2\n");
		AVLDestroy(avl);
		return 1;
	}
	AVLDestroy(avl);	
	return 0;
}
