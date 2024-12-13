#include <stdio.h> /*printf*/



#include "bit_array.h"

static void PrintBit(bit_array_t bit_arr);
static void TestSetAll(bit_array_t number);
static void TestResetAll(bit_array_t number);
static void TestSetOn(bit_array_t number, size_t index);
static void TestSetOff(bit_array_t number, size_t index);
static void TestSetBit(bit_array_t number, size_t index,int bool_value);
static void TestGetVal(bit_array_t number, size_t index);
static void TestFlipBit(bit_array_t number, size_t index);
static void TestFlipAll(bit_array_t number);
static void TestMirror(bit_array_t number);
static void TestRotateRight(bit_array_t number, size_t n);
static void TestRotateLeft(bit_array_t number, size_t n);
static void TestToString(bit_array_t number, char *dest);
static void TestCountOn(bit_array_t number);
static void TestCountOff(bit_array_t number);
static void TestMirrorLut(bit_array_t number);

int main(void)
{
	bit_array_t number = 0xad452e;
	size_t index = 3;
	int bool_value = 0;
	size_t n = 62;
	char dest[100];
	TestSetAll(number);
	TestResetAll( number);
	TestSetOn( number , index);
	TestSetOff( number , index);
	TestSetBit( number,  index, bool_value);
	TestGetVal(number,  index);
	TestFlipBit(number,  index);
	TestFlipAll( number);
	TestMirror( number);
	TestMirrorLut( number);
	TestRotateRight( number,  n);
	TestRotateLeft( number,  n);	
	 TestToString( number,  dest);
	 TestCountOn( number);
	 TestCountOff( number);
	return 0;
}

/*test function*/
/*print function for check*/
static void PrintBit(bit_array_t bit_arr)
{
	int i = 0;
	int count = 0;
	for(i = 63; i >= 0; --i) 
	{
		printf("%ld", (bit_arr >> i) & 1);
		++count;
		if(8 == count)
		{
			printf("\n");
			count =0;
		}
	}
}
static void TestSetAll(bit_array_t number)
{	
	printf("***************** start of test SetAll***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after SetAll :\n");
	number = SetAll(number);
	PrintBit(number);
	printf("***************** end of test SetAll***************************\n");
}
static void TestResetAll(bit_array_t number)
{	
	printf("***************** start of TestResetAll***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after ResetAll :\n");
	number = ResetAll(number);
	PrintBit(number);
	printf("***************** end of TestResetAll***************************\n");
}

static void TestSetOn(bit_array_t number, size_t index)
{	
	printf("***************** start of TestSetOn***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after SetOn :\n");
	number = SetOn(number ,index);
	PrintBit(number);
	printf("***************** end of TestSetOn***************************\n");
}

static void TestSetOff(bit_array_t number, size_t index)
{	
	printf("***************** start of TestSetOff***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after TestSetOff :\n");
	number = SetOff(number ,index);
	PrintBit(number);
	printf("***************** end of TestSetOff***************************\n");
}
static void TestSetBit(bit_array_t number, size_t index,int bool_value)
{	
	printf("***************** start of TestSetBit***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after TestSetBit :\n");
	number = SetBit(number ,index ,bool_value);
	PrintBit(number);
	printf("***************** end of TestSetBit***************************\n");
}

static void TestGetVal(bit_array_t number, size_t index)
{	
	int bit =546;
	printf("***************** start of GetVal***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after GetVal :\n");
	printf("index is:%ld \n, ",index);
	bit = GetVal(number ,index);
	printf("the bits is:%d \n, ",bit);
	printf("***************** end of GetVal***************************\n");
}
static void TestFlipBit(bit_array_t number, size_t index)
{	
	printf("***************** start of FlipBit***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after FlipBit :\n");
	printf("index is:%ld \n",index);
	number = FlipBit(number ,index);
	PrintBit(number);
	printf("***************** end of FlipBit***************************\n");
}
static void TestFlipAll(bit_array_t number)
{	
	printf("***************** start of FlipAll***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after FlipAll :\n");
	number = FlipAll(number);
	PrintBit(number);
	printf("***************** end of FlipAll***************************\n");
}

static void TestMirror(bit_array_t number)
{	
	printf("***************** start of Mirror***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after Mirror :\n");
	number = Mirror(number);
	PrintBit(number);
	printf("***************** end of Mirror***************************\n");
}
static void TestMirrorLut(bit_array_t number)
{	
	printf("***************** start of Mirrorwithlut***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after Mirror :\n");
	number = MirrorLut(number);
	PrintBit(number);
	printf("***************** end of Mirrorwithlut***************************\n");
}

static void TestRotateRight(bit_array_t number, size_t n)
{	
	printf("***************** start of RotateRight***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after RotateRight :\n");
	printf("n is: %ld\n", n);
	number = RotateRight(number, n);
	PrintBit(number);
	printf("***************** end of RotateRight***************************\n");
}

static void TestRotateLeft(bit_array_t number, size_t n)
{	
	printf("***************** start of RotateLeft***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after RotateRight :\n");
	printf("n is: %ld\n", n);
	number = RotateLeft(number, n);
	PrintBit(number);
	printf("***************** end of RotateLeft***************************\n");
}
static void TestToString(bit_array_t number, char *dest)
{	
	printf("***************** start of ToString***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after RotateRight :\n");
	dest = ToString(number, dest);
	printf("dest: %s\n",dest );
	printf("***************** end of ToString***************************\n");
}

static void TestCountOn(bit_array_t number)
{	
	size_t bit = 0;
	printf("***************** start of CountOn***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after CountOn :\n");
	bit = CountBitsOnLut(number );
	printf("the number o bit on is:%ld \n, ",bit);
	printf("***************** end of CountOn***************************\n");
}
static void TestCountOff(bit_array_t number)
{	
	size_t bit = 0;
	printf("***************** start of CountOff***************************\n");
	printf("the bits before :\n");
	PrintBit(number);
	printf("the bits after CountOn :\n");
	bit = CountOff(number );
	printf("the number o bit off is:%ld \n, ",bit);
	printf("***************** end of CountOff***************************\n");
}
