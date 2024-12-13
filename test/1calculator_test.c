#include <stdio.h>/*printf*/
#include <stdlib.h> /*strtod*/
#include <string.h>/*stringgg*/

#include "calculator.h"

#define TESTNUM 5

int first_test(char *str);
int testnum2(char *str2);

static char failed_tests_print[200] = {'\0'};



void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}



int main(void)
{
	int failed_tests_num = 0;
	
	char *str = "(7 +8)*2 "; 
					  					/*Result = 15 status = CALC_SUCCESS */
	char str2[100] = "3^-1";		  /*Result =  0 status = CALC_SUCCESS*/
	
	char str3[100] = "8+8*3-2^1";		  /*Result =  0 status = CALC_SYNTAX_ERROR  */
	char str4[100] = "2/0";				  /*Result =  0 status = CALC_MATH_ERROR    */
	char str5[100] = "8++8*((3-2)*5)";	  /*Result = 48 status = CALC_SUCCESS 	   */
	char str6[100] = "3-2)*5";			  /*Result =  0 status = CALC_SYNTAX_ERROR  */
	char str7[100] = "(3-2)*5+ 5*(4+4+4"; /*Result =  0 status = CALC_SYNTAX_ERROR*/ 
	char str8[100] = "4-3-2-1\n";		  /*Result =  -2 status = CALC_SUCCESS  */
	char str9[100] = "4^3^2^1\n";		  /*Result =  4096 status = CALC_SUCCESS*/ 
	
	
	failed_tests_num += first_test(str);
	printf("Tested first_test\n");
	failed_tests_num += testnum2(str2);
	printf("Tested testnum2\n");
	/*failed_tests_num += third_test();
	printf("Tested third_test\n");
	failed_tests_num += test_num4();
	printf("Tested test_num4\n");
	failed_tests_num += test_num5();
	printf("Tested test_num5\n");*/
	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	

    return 0;
    
}  
  
int first_test(char *str)
{

	double res = 0;
	Calculate(str ,&res);
	printf("the result in test 1 is ; %f\n", res);
	if(res != 30)
	{
		printf("the result in test 1 is ; %f", res);
		AddFailedTest("test 1\n");
		return 1;
	}
	
	return 0;
}
int testnum2(char *str2)
{

	double res = 0;
	Calculate(str2 ,&res);
	if(res != 3)
	{
		printf("the result in test 2 is ; %f\n", res);
		AddFailedTest("test 2\n");
		return 1;
	}
	
	return 0;
}
int testnum3(char *str3)
{

	double res = 0;
	Calculate(str3 ,&res);
	if(res != 30)
	{
		printf("the result in test 2 is ; %f\n", res);
		AddFailedTest("test 2\n");
		return 1;
	}
	
	return 0;
}

int testnum4(char *str4)
{

	double res = 0;
	Calculate(str4 ,&res);
	if(res != 0)
	{
		printf("the result in test 2 is ; %f\n", res);
		AddFailedTest("test 2\n");
		return 1;
	}
	
	return 0;
}

int testnum5(char *str5)
{

	double res = 0;
	Calculate(str ,&res);
	if(res != 0)
	{
		printf("the result in test 2 is ; %f\n", res);
		AddFailedTest("test 2\n");
		return 1;
	}
	
	return 0;
}

