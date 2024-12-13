/*#include <stddef.h>*/ /*size_t*/
/*#include <stdio.h>*/ /*printf*/
/*
#include "/home/ido/git/ds/include/stack.h"

int main()
{	
	int val = 14;
	int *ptr_val = &val;
	int arr[1] = {0};
	int empty = 0;
	size_t capacity = 0;
	size_t size = 0;
	stack_t *test_stack = StackCreate(10, sizeof(int));
	
	StackPush(test_stack, ptr_val);
	size = StackSize(test_stack);
	printf("the stack size is: %ld\n", size);
	StackPeek(test_stack, arr);
	printf("peek :%d\n", arr[0]);
	val = 20;
	StackPush(test_stack, ptr_val);
	size = StackSize(test_stack);
	printf("the stack size is: %ld\n", size);
	StackPeek(test_stack, arr);
	printf("peek :%d\n", arr[0]);
	empty = StackIsEmpty(test_stack);
	printf("IF EMPTY == 1 %d\n", empty);
	capacity = StackCapacity(test_stack);
	printf("the stack capacity is: %ld\n", capacity);
	StackPop(test_stack);
	size = StackSize(test_stack);
	printf("the stack size is: %ld\n", size);
	StackPeek(test_stack, arr);
	printf("peek :%d\n", arr[0]);
	StackDestroy(test_stack);
	
	return 0;
	
	
}*/ 
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* free */

#include "stack.h"

struct stack;

typedef enum status_code_t
{
	SUCCESS = 0,
	STACK_MEMBERS_FAIL = -1,
	STACK_PEEK_FAIL = -2,
	STACK_WRONG_FIRST_ITEM = -3,
	STACK_WRONG_CURRENT_SIZE = -4,
	STACK_WRONG_CAPACITY = -5
} status_code_t;

static void TestStack();
static void TestStackIntHelper(size_t capacity , size_t type_size, char *test_number);
static status_code_t CheckStackMembers(stack_t *stack, size_t capacity);
static status_code_t CheckPeekFunc(stack_t *stack, int num_1, size_t type_size);
static void ShowErrorMessageAndFree(stack_t *stack, int code_status);
static status_code_t CheckBufferCurrentSize(stack_t *stack, size_t size);
static status_code_t CheckBufferCapacity(stack_t *stack, size_t size);

int main()
{

	TestStack();
	
	return 0;
}

static void TestStack()
{	
	TestStackIntHelper(32, 4, "test 1");
	TestStackIntHelper(10, 4, "test 2");
	TestStackIntHelper(18, 9, "test 3");
	TestStackIntHelper(19, 5, "test 4");
}

static void TestStackIntHelper(size_t capacity , size_t type_size, char *test_number)
{
	stack_t *stack = NULL;
	int func_status_code = 0;
	size_t stack_curr_size = 0;
	int num = 5;
	
	printf("***************************** start %s  *****************************\n\n", test_number);
	stack = StackCreate(capacity, type_size);
	if(NULL == stack)
	{
		printf("failed to create stack");
	}
	func_status_code = CheckStackMembers(stack, capacity);
	ShowErrorMessageAndFree(stack, func_status_code);
	
	if(SUCCESS != func_status_code)
	{
		return;
	}
	
	StackPush(stack, &num);
	++stack_curr_size;
	func_status_code = CheckPeekFunc(stack, num, type_size);
	ShowErrorMessageAndFree(stack, func_status_code);
	if(SUCCESS != func_status_code)
	{
		return;
	}
	
	func_status_code = CheckBufferCurrentSize(stack, stack_curr_size);
	ShowErrorMessageAndFree(stack, func_status_code);
	if(SUCCESS != func_status_code)
	{
		return;
	}
	
	func_status_code = CheckBufferCapacity(stack, capacity);
	ShowErrorMessageAndFree(stack, func_status_code);
	if(SUCCESS != func_status_code)
	{
		return;
	}
	num = 9;
	StackPush(stack, &num);
	num = 3;
	StackPush(stack, &num);
	num = 95;
	StackPush(stack, &num);
	
	stack_curr_size += 3;
	
	func_status_code = CheckBufferCurrentSize(stack, stack_curr_size);
	ShowErrorMessageAndFree(stack, func_status_code);
	if(SUCCESS != func_status_code)
	{
		return;
	}
	
	StackPop(stack);	
	--stack_curr_size;
	
	func_status_code = CheckBufferCurrentSize(stack, stack_curr_size);
	ShowErrorMessageAndFree(stack, func_status_code);
	if(SUCCESS != func_status_code)
	{
		return;
	}
	num = 3;
	func_status_code = CheckPeekFunc(stack, num, type_size);
	ShowErrorMessageAndFree(stack, func_status_code);
	if(SUCCESS != func_status_code)
	{
		return;
	}
	
	
	func_status_code = StackIsEmpty(stack);
	if(func_status_code == 1)
	{
		printf("stack should not be empty !!!!!!!!!\n");
		StackDestroy(stack);
		return;
	}
	StackPop(stack);	
	--stack_curr_size;
	StackPop(stack);	
	--stack_curr_size;
	StackPop(stack);	
	--stack_curr_size;
	
	func_status_code = StackIsEmpty(stack);
	if(func_status_code == 0)
	{
		printf("stack sould be empty !!!!!!!!!\n");
	}
	
	
	StackDestroy(stack);
	printf("\n***************************** end %s  *****************************\n\n", test_number);
}

static status_code_t CheckBufferCapacity(stack_t *stack, size_t size)
{
	size_t buffer_capacity = 0;
	
	buffer_capacity = StackCapacity(stack);
	if(size == buffer_capacity)
	{
		printf("size %ld is equal to buffer capacity %ld\n", buffer_capacity, size);
	}
	else
	{
		printf("size %ld is not equal to buffer capacity %ld\n", buffer_capacity, size);
		return STACK_WRONG_CAPACITY;
	}
	
	return SUCCESS;
}



static status_code_t CheckBufferCurrentSize(stack_t *stack, size_t size)
{
	size_t buffer_current_size = 0;
	
	buffer_current_size = StackSize(stack);
	if(size == buffer_current_size)
	{
		printf("size %ld is equal to buffer current size %ld\n", buffer_current_size, size);
	}
	else
	{
		printf("size %ld is not equal to buffer current size %ld\n", buffer_current_size, size);
		return STACK_WRONG_CURRENT_SIZE;
	}
	
	return SUCCESS;
}

static status_code_t CheckPeekFunc(stack_t *stack, int num_1, size_t type_size)
{
	int *peek_item = NULL;
	
	assert(NULL != stack);
	peek_item = (int *)malloc(type_size);
	StackPeek(stack, peek_item);
	if(NULL == peek_item)
	{
		return STACK_PEEK_FAIL;
	}
	if(*peek_item == num_1)
	{
		printf("success - item %d is the same as first item %d in the stack\n", num_1, *peek_item);
	}
	else
	{
		printf("failed - item %d is not the same as first item %d in the stack\n", num_1, *peek_item);
		free(peek_item);
		return STACK_WRONG_FIRST_ITEM;
	}
	free(peek_item);
	
	return SUCCESS;
}

static status_code_t CheckStackMembers(stack_t *stack, size_t capacity)
{
	assert(NULL != stack);
	
	if(capacity == StackCapacity(stack))
	{
		printf("Capacity insertion success\n");
	}
	else
	{
		printf("Capacity insertion failed\n");
	}
	if(1 == StackIsEmpty(stack))
	{
		printf("empty buffer creation success\n");
	}
	else
	{
		printf("empty buffer creation failed\n");
	}
	
	return SUCCESS;
}

static void ShowErrorMessageAndFree(stack_t *stack, int code_status)
{
	switch(code_status)
	{
		case SUCCESS:
			break;
		case STACK_MEMBERS_FAIL:
			printf("Error with CheckStackMembers function\n");
			StackDestroy(stack);
			break;
		case STACK_PEEK_FAIL:
			printf("Error with CheckPeekFunc function\n");
			StackDestroy(stack);
			break;
		case STACK_WRONG_FIRST_ITEM:
			StackDestroy(stack);
			break;
		case STACK_WRONG_CURRENT_SIZE:
			StackDestroy(stack);
			break;
		case STACK_WRONG_CAPACITY:
			StackDestroy(stack);
			break;
		default:
			break;
	}
}

