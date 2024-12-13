#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <stdlib.h>

#include "vsa.h"
/*goes to sheet at 107*/
#define TESTNUM 2

static char failed_tests_print[200] = {'\0'};

static int TestVSAAlloc(void);
static int TestLargestChunkAvailable(void);

void AddFailedTest(const char *str);

void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}
int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestVSAAlloc();
	printf("Tested VSAAlloc\n");

	failed_tests_num += TestLargestChunkAvailable();
	printf("Tested LargestChunkAvailable\n");

	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}
static int TestVSAAlloc(void)
{
	void *allocated_space = NULL;
	vsa_t *memory_pool = NULL;
	size_t total_size = 1000;
	size_t *elements[20] = {NULL};
	size_t *block = NULL;
	size_t loop_count = 0;

	size_t blocks_allocated = 0;
	
	allocated_space = malloc(total_size);
	memory_pool=VSAInit(allocated_space, total_size);
	
	elements[loop_count] = (size_t *)VSAAlloc(memory_pool, 80);
	VSAFree(elements[0]);
	
	if( LargestChunkAvailable(memory_pool) < total_size-968)
	{
		AddFailedTest("TestVSAAlloc\n");
				free(allocated_space);
				return 1;
	}
	
	while(LargestChunkAvailable(memory_pool) > 80)
	{
		elements[loop_count] = (size_t *)VSAAlloc(memory_pool, 80);
		++loop_count;
	}
	
	blocks_allocated = loop_count;
	loop_count = 0;
	
	while(loop_count >= blocks_allocated)
	{
		if(!elements[loop_count])
		{
			AddFailedTest("TestVSAAlloc2\n");
				free(allocated_space);
				return 1;
		}
	}
	block = (size_t *)VSAAlloc(memory_pool, 160);
	if (block)
	{
		AddFailedTest("TestVSAAlloc3\n");
		free(allocated_space);
		return 1;
	}
	
	VSAFree(elements[0]);
	
	
	block = (size_t *)VSAAlloc(memory_pool, 80);
	
	if (!block)
	{
		AddFailedTest("TestVSAAlloc3\n");
		free(allocated_space);
		return 1;
	}
	printf("\n the largest size is : %ld \n", LargestChunkAvailable(memory_pool));
	printf("\n the number of blocks_allocated : %ld \n",blocks_allocated);
	
	free(allocated_space);
	
	return 0;
}




static int TestLargestChunkAvailable(void)
{
	
	void *allocated_space = NULL;
	vsa_t *memory_pool = NULL;
	size_t total_size = 1000;
	size_t *elements[20] = {NULL};
	size_t loop_count = 0;
	size_t previous_largest_chunk = 0;
	
	allocated_space = malloc(total_size);
	memory_pool = VSAInit(allocated_space, total_size);
	
	
	/* checks if LargestChunkAvailable decreases after every alloc */
	
	previous_largest_chunk = LargestChunkAvailable(memory_pool);
	while(loop_count < 6)
	{
		elements[loop_count] = (size_t *)VSAAlloc(memory_pool, 80);
		++loop_count;
		
		if (previous_largest_chunk <= LargestChunkAvailable(memory_pool))
		{
			AddFailedTest("TestLargestChunkAvailable1\n");
			free(allocated_space);
			return 1;
		}
		previous_largest_chunk = LargestChunkAvailable(memory_pool);
	}
	
	/* checks if LargestChunkAvailable increases after every free */
	
	previous_largest_chunk = LargestChunkAvailable(memory_pool);
	--loop_count;
	while(loop_count > 0)
	{
		VSAFree(elements[loop_count]);
		--loop_count;
		
		if (previous_largest_chunk >= LargestChunkAvailable(memory_pool))
		{
			AddFailedTest("TestLargestChunkAvailable2\n");
			free(allocated_space);
			return 1;
		}
		previous_largest_chunk = LargestChunkAvailable(memory_pool);
	}
	
	free(allocated_space);

	return 0;
}

