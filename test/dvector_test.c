#include <stdio.h> /* printf() */

#include "dvector.h"





int main()
{
	int x = 15;
	size_t new_capacity = 0;
	size_t size =0;
	int count = 0;
	
	dvector_t *dvector =  DvectorCreate(3, sizeof(int));
	if(NULL == dvector)
	{
		printf("dvector create faild\n");
	}
	else
	{
		printf("dvector create sucseed\n");
		++count;
	}
	
	
	printf("*********push test for 15*********\n");
	DvectorPushBack(dvector, &x );
	/*test get element  + push regular */
	printf("the capasity is: %ld \n" , DvectorCapacity(dvector) );
		printf("\n \n x  is: %d \n" ,x );
	if(x ==*( (int *)DvectorGetElement(dvector,0)) )
	{
		printf("the index 0 is: %d \n\n", *( (int *)DvectorGetElement(dvector,0)));
		/*printf(" DvectorPushBack sucseed\n");
		printf(" and obviously DvectorGetElement  sucseed\n");*/
		++count;
	}
	else
	{
			printf("DvectorPushBack faild\n");
	}
	
	x = 0;
	/*test get element  + push over size */
	
	DvectorPushBack(dvector, &x );
	
	printf("\n \n x  is: %d \n" ,x );
	
	if(x ==*( (int *)DvectorGetElement(dvector,1)) )
	{
		printf("the index 1 is: %d \n", *( (int *)DvectorGetElement(dvector,1)));
		++count;
	}
	else
	{
			printf("DvectorPushBack faild\n");
	}
	
	x = 3524;
	
	DvectorPushBack(dvector, &x );
	printf("\n \n x  is: %d \n" ,x );
	if(x ==*( (int *)DvectorGetElement(dvector,2)) )
	{
		printf("the index 2 is: %d \n", *( (int *)DvectorGetElement(dvector,2)));
		++count;
	}
	else
	{
			printf("DvectorPushBack faild\n");
	}

	printf("\nthe capasity is: %ld \n" , DvectorCapacity(dvector) );
	new_capacity = DvectorCapacity(dvector);
	
	printf("\n*********tEST FOR AUTO CAPASITY INCREASE*********\n");
	/*TEST FOR AUTO CAPASITY INCREASE*/
	x = 45 ;
	DvectorPushBack(dvector, &x );
	if(x ==*( (int *)DvectorGetElement(dvector,3)) )
	{
		printf(" test sucseed the index 3 is: %d \n\n", *( (int *)DvectorGetElement(dvector,3)));
		++count;
	}
	else
	{
			printf("DvectorPushBack faild\n");
	}
	printf("the size is: %ld \n" , DvectorSize(dvector) );
	size =DvectorSize(dvector);
	/*printf("the capasity is: %ld \n" , DvectorCapacity(dvector) );*/
	
	if(x ==*( (int *)DvectorGetElement(dvector,3))&&  new_capacity*2 == DvectorCapacity(dvector))
	{
		printf("the index 0 is: %d \n", *( (int *)DvectorGetElement(dvector,0)));
		printf(" DvectorPushBack and  realloc sucseed\n");
		printf(" realloc sucseed \n");
		++count;
	}
	else
	{
			printf("DvectorPushBack faild\n");
	}
	
	/*pop*/
	printf("\n*********DvectorPopBack*********\n");
	DvectorPopBack(dvector);
	printf("the size is: %ld \n" , DvectorSize(dvector) );
	printf("the capasity is: %ld \n" , DvectorCapacity(dvector) );
	
	if(DvectorSize(dvector) == size - 1)
	{
		printf(" DvectorPopBack sucseed\n");
		++count;

	}
	else
	{
		printf(" DvectorPopBack failed\n");
	}
	
	printf("\n*********shrink test*********\n");
	/*shrink*/
	
	DvectorShrink(dvector);
	if( DvectorSize(dvector) == DvectorCapacity(dvector))
	{
		printf(" DvectorShrink sucseed\n");
		++count;
	}
	else
	{
		printf(" DvectorShrink failed\n");
	}
	printf("the size is: %ld \n" , DvectorSize(dvector) );
	printf("the capasity is: %ld \n" , DvectorCapacity(dvector) );
	
	printf("\n*********reserve test*********\n");
	printf("\nexpend capasity to 10\n");
	DvectorReserve(dvector, 10);
	if(10 == DvectorCapacity(dvector))
	{
		printf(" DvectorCapacity sucseed\n");
		++count;
	}
	else
	{
		printf(" DvectorCapacity failed\n");
	}
	printf("the size is: %ld \n" , DvectorSize(dvector) );
	printf("the capasity is: %ld \n" , DvectorCapacity(dvector) );
	
	/*shrink*/
	printf("\n*********shrink test*********\n");
	DvectorShrink(dvector);
	
	if( DvectorSize(dvector) == DvectorCapacity(dvector))
	{
		printf(" DvectorShrink sucseed again\n");
		++count;
	}
	else
	{
		printf(" DvectorShrink failed\n");
	}
	/*printf("the size is: %ld \n" , DvectorSize(dvector) );
	printf("the capasity is: %ld \n" , DvectorCapacity(dvector) );*/
	
	if( 10 == count)
	{
		printf("all tests works\n");
	}
	else 
	{
		printf("%d operation failed\n", 10 - count);
	}
	
	DvectorDestroy(dvector);
    return 0;
}

