#include <stdio.h> /*printf*/
#include <stddef.h>
#include <time.h>
#include <stdlib.h>

#include "sort.h"
void TestHelper ( int num ,int index, char *str);
int TestBinarySort();
int TestBinarySortRecursive();
static int Compare(const void *num1, const void *num2);
void Creat2Arr(int arr[], int arr2[]);
void TestMergeHelper(int *arr1, int *arr2);
int TestMergeSort();
void TestQuickHelper(int *arr1, int *arr2);
int TestQuickSort();

int main(void)
{
	TestBinarySort();
	printf("\n\n");
	TestBinarySortRecursive();
	printf("\n\n");
	TestMergeSort();
	TestQuickSort();
	
	return 0;
}

int TestBinarySort()
{
	int arr[] = {0,2,5,6,15,20,25,27,30,74,80};
	int k = 74;
	int index = BinarySearchIterative(arr , 11 , k);
	TestHelper(9 , index , "first test for binary");
	TestHelper(1, index = BinarySearchIterative(arr,11,2),"secound test for binary");
	TestHelper(-1, index = BinarySearchIterative(arr,11,65),"third test for binary");
	TestHelper(10, index = BinarySearchIterative(arr,11,80),"4 test for binary");

	
	return 0;
}

int TestBinarySortRecursive()
{
	int arr[] = {0,2,5,6,15,20,25,27,30,74,80};
	int k = 74;
	int index = BinarySearchIterative(arr , 11 , k);
	TestHelper(9 , index , "first test for binary recursive");
	TestHelper(1, index = BinarySearchRecursive(arr,0, 11 ,2),
								"secound test for binary recursive");
	TestHelper(-1, index = BinarySearchRecursive(arr,0, 11,65),
								  "third test for binary recursive");
	TestHelper(10, index = BinarySearchRecursive(arr,0 ,11 ,80),
								"test num 4 for binary recursive");
	TestHelper(0, index = BinarySearchRecursive(arr,0 ,11 ,0),
								"test num 4 for binary recursive");
								
	return 0;
}

int TestQuickSort()
{
	int arr1[500];
	int arr2[500];
	int i =0;
	Creat2Arr(arr1, arr2);
	
	Qsort(arr1, 500, sizeof(int), Compare);
	/*for (; i < 500; i++) 
	{
    	printf("%d ", arr1[i]);
	}*/
		printf("\n ");
	qsort(arr2 , 500 , sizeof(int),Compare);
	
	TestQuickHelper( arr1 , arr2 );
							
	return 0;
}

void TestQuickHelper(int *arr1, int *arr2)
{
	int i =0;
	
	for(;i< 500; ++i)
	{
		if(arr1[i] != arr2[i])
		{
			printf("Quick sort faild\n");
			
			return;
		}
	}
	
	printf("Quick sort worked \n");
}

int TestMergeSort()
{
	int arr1[500];
	int arr2[500];
	int i =0;
	Creat2Arr(arr1, arr2);
	
	MergeSort(arr1, 500);
	/*for (; i < 500; i++) 
	{
    	printf("%d ", arr1[i]);
	}*/
		printf("\n ");
	qsort(arr2 , 500 , sizeof(int),Compare);
	
	TestMergeHelper( arr1 , arr2 );
							
	return 0;
}

void TestMergeHelper(int *arr1, int *arr2)
{
	int i =0;
	
	for(;i< 500; ++i)
	{
		if(arr1[i] != arr2[i])
		{
			printf("merge sort faild\n");
			
			return;
		}
	}
	
	printf("merge sort worked \n");
}
void Creat2Arr(int arr[], int arr2[])
{
	int i = 0;
	for (; i < 500; i++) 
	{
    	 arr[i] = rand() % 100;
    	 arr2[i]= arr[i];
	}
}

void TestHelper ( int num ,int index, char *str)
{
	if(num != index)
	{
		printf("%s faild\n", str);

	}
	else
	{
		printf("%s sucssed\n", str);
	}
}

static int Compare(const void *num1, const void *num2)
{
	return *(int *)num1 - *(int *)num2;
}
