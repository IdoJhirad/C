#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "avl.h"

#define TESTNUM 4

static int TestCreatAndDystroy();
static int BabyTestForEmptyCountHightInsert();
static int  TestForEmptyCountHightInsert();
static int InsetAndHeightTest2();
static int RemoveInBalace();
static int TestRemove();
static int TestCreatAndDystroy();
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
	failed_tests_num += InsetAndHeightTest2();
	printf("Tested InsetAndHeightTest2\n");
	failed_tests_num +=RemoveInBalace();
	printf("Tested RemoveInBalace\n");
	failed_tests_num +=TestForEmptyCountHightInsert();
	printf("Tested TestForEmptyCountHightInsert\n");
	failed_tests_num +=TestRemove();
	printf("Tested TestRemove\n");
	
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
/*test for hight check after rotation */
static int BabyTestForEmptyCountHightInsert()
{
	int arr[] = {15 ,20 ,3,19, 21 ,30 ,74, 2, 5, 4 ,62,6, 7, 25, 0, 80};

	avl_t *avl = AVLCreate(Compare);


	if(!avl)
	{
		AddFailedTest("create faild");
		return 1;
	}
	
	if( AVLHeight(avl))
	{
		AddFailedTest("hight faild  1\n");
		AVLDestroy(avl);
		return 1;
	}
	
	AVLInsert(avl, arr + 0);
	if( 1 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert 1\n");
		AVLDestroy(avl);
		return 1;
	}
	
	AVLInsert(avl, arr + 1);
	if( 2 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert 1\n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 2);
	AVLInsert(avl, arr + 3); /*19*/
	AVLInsert(avl, arr + 4); /*21*/
	if( 3 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert 1\n");
		AVLDestroy(avl);
		return 1;
	}
	/*20 should rotate left and stay at hight 3*/
	AVLInsert(avl, arr + 5); /*30*/
	if( 3 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert 1\n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 6); /*74 another left roattion*/ 
	if( 3 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert 1\n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 7); /*2 another layer*/
 	AVLInsert(avl, arr + 8); /*5 */
	if( 4 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in BabyTestForEmptyCountHightInsert 1\n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 9); /*4 should do a right left */
	if( 4 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in  1\n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 10); /*62*/
	if( 4 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in  1\n");
		AVLDestroy(avl);
		return 1;
	}
			printf("\n\n");
/*	AVLForEach(avl ,PrintNode , &num );	*/
/*	printf("\n\n");*/
	AVLInsert(avl, arr + 11); /*6 */
/*	AVLForEach(avl ,PrintNode , &num );	*/
/*	printf("\n\n");*/
/*	printf("\n %ld \n", AVLHeight(avl));*/
	if( 4 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion 6 \n");
		AVLDestroy(avl);
		return 1;
	}
	
	AVLInsert(avl, arr + 11); /*7 */
	AVLInsert(avl, arr + 12); /*25 */
	if(  5 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 13); /*0 */
	if(  5 !=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLDestroy(avl);
	
	return 0;
}
static int InsetAndHeightTest2()
{
	int arr[] = {10, 20, 30, 5, 6 , 60};
	int arr2[]= {10,20,30,40,50,60,70,80,90,100,110,120};
	int num = 0;
	size_t index = 0;
	avl_t *avl = AVLCreate(Compare);

	AVLInsert(avl, arr + 0); /*10 */
	if(  1!=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 1); /*20 */
	if(   2!=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 2); /*30 */
	if(  2!=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLInsert(avl, arr + 3); /*5 */
	if(  3!=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
/*		20			*/
/*		/\			*/
/*	10	  30		*/
/*	/				*/
/*  5				*/
/*   \				*/
/*   6				*/
	AVLInsert(avl, arr + 3); /*6 */
	if(  3!=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
	if(  5!=AVLCount(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLDestroy(avl);
	
	
	avl = AVLCreate(Compare);
	for(; index < 11; ++index)
	{
	
		if(AVLCount(avl) != index)
		{
			AddFailedTest("Count faild to keep up \n");
			printf("count is %ld, index is %ld \n",index, AVLCount(avl));
			printf("the itration that faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
		num = AVLInsert(avl, arr2 + index);

		if(0 !=num )
		{
			AddFailedTest("insert statud return faild \n");
			printf("the itration thai faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
	}	

	if(  4!=AVLHeight(avl))
	{
		AddFailedTest("hight faild in in isertion  25 \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLDestroy(avl);
	return 0;	
}

static int RemoveInBalace()
{
	int arr[] = {15 ,20 ,3,19, 21 ,30 ,74, 2, 5, 4 ,62 ,6, 7, 25, 0, 80};
	int num = 0;/*0  1   2  3  4   5   6   7  8  9  10 11 12 13  14 15*/
	size_t index = 0; 
	avl_t *avl = AVLCreate(Compare);
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
		num = AVLInsert(avl, arr + index);

		if(0 !=num )
		{
			AddFailedTest("insert statud return faild \n");
			printf("the itration thai faild is %ld\n", index);
			AVLDestroy(avl);
			return 1;
		}
	}	
	if( 5 != AVLHeight(avl))
	{
		AddFailedTest("count failed in remove \n");
		AVLDestroy(avl);
		return 1;
	}
	/* remove 19 case left right*/
	AVLRemove(avl, arr + 14);/*0 leaf */
	AVLRemove(avl, arr + 3);/*19*/
	if( 4 != AVLHeight(avl))
	{
		AddFailedTest("hight failed in remove \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLRemove(avl, arr + 12);/*7*/
	AVLRemove(avl, arr + 0);/*15*/
	AVLRemove(avl, arr + 11);/*6*/
	AVLRemove(avl, arr + 9);/*4*/
	AVLRemove(avl, arr + 7);/*2*/
	AVLRemove(avl, arr + 8);/*5*/
	AVLRemove(avl, arr + 13);/*25*/
	if( 3 != AVLHeight(avl))
	{
		AddFailedTest("hight failed in remove \n");
		AVLDestroy(avl);
		return 1;
	}
	AVLDestroy(avl);
	return 0;
}	

static int TestForEmptyCountHightInsert()
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
	}
	num = AVLInsert(avl, arr + index);
	if(0 !=num )
	{
		AddFailedTest("insert statud return faild \n");
		printf("the itration thai faild is %ld\n", index);
		AVLDestroy(avl);
		return 1;
	}	

	-- index;
	

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
	/*printf( "\n count : %ld\n ", AVLCount(avl));
	printf("\n ");*/
	
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






