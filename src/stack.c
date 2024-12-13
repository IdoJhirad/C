#include <string.h>/*memcpy*/
#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc free*/

#include "stack.h"
/***********************************************
Name: Ido
Reviewer: sahar
Exercise: stack
Status: Done
***********************************************/ 

#include <stdio.h> /* printf, size_t */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "stack.h"
 

struct stack
{
    void *buffer;
    size_t capacity;
    size_t type_size;
    size_t current_size;
};

stack_t *StackCreate(size_t capacity, size_t type_size)
{

	stack_t *stack = (stack_t *)malloc(sizeof(stack_t) + (capacity * type_size));
	
	stack->buffer = stack + 1;
	stack->current_size = 0;
	stack->type_size = type_size;
	stack->capacity = capacity;
	
	
	return stack;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack);
	stack = NULL;
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	
	if(0 == stack->current_size)
	{
		return;
	}
	--(stack->current_size);
}

void StackPush(stack_t *stack, const void *item)
{
	char *buff = NULL, *char_item = NULL;
	
	assert(NULL != stack);
	buff = (char *)stack->buffer;
	char_item = (char *)item;
	
	memcpy((char *)(buff + (stack->current_size * stack->type_size)), char_item, stack->type_size);
	++(stack->current_size);
}
void StackPeek(const stack_t *stack, void *dest)
{
	char *buff = NULL, *dest_char = NULL;
	
	assert(NULL != stack);
	
	buff = (char *)stack->buffer;
	dest_char = (char *)dest;
	
	if(0 == stack->current_size)
	{
		return ;
	}
		
	buff = (char *)stack->buffer;
	memcpy(dest_char, buff + ((stack->current_size - 1) * stack->type_size), stack->type_size);

}


size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->current_size;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	return ((stack->capacity - stack->current_size) == stack->capacity) ? 1 : 0 ;
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->capacity;
}










