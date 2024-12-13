#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <stdlib.h>

#include "fsa.h"

#define TESTNUM 4

static char failed_tests_print[200] = {'\0'};

static int TestFSASuggestSize(void);
static int TestFSAAlloc(void);
static int TestFSAFree(void);
static int TestFSACountFree(void);

void AddFailedTest(const char *str);

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestFSASuggestSize();
	printf("Tested FSASuggestSize\n");
	failed_tests_num += TestFSAAlloc();
	printf("Tested FSAAlloc\n");
	failed_tests_num += TestFSAFree();
	printf("Tested FSAFree\n");
	failed_tests_num += TestFSACountFree();
	printf("Tested FSACountFree\n");

	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}


void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}

static int TestFSASuggestSize(void)
{
	size_t suggested_size = 0;
	void *allocated_space = NULL;
	fsa_t *memory_pool = NULL;
	size_t block_size = 200;
	size_t block_num = 8;
	size_t actual_block_num = 0;
	
	/* checks if suggested size is actually enough for storing block_num
		blocks of block_size size*/
	
	suggested_size = FSASuggestSize(block_size, block_num);
	allocated_space = malloc(suggested_size);
	
	memory_pool = FSAInit(allocated_space, suggested_size, block_size);
	actual_block_num = FSACountFree(memory_pool);
	
	if (actual_block_num != block_num)
	{
		AddFailedTest("TestFSASuggestSize1\n");
		free(allocated_space);
		return 1;
	}
	
	free(allocated_space);
	
	/* checks if suggested size is actually the minimum size required
	 for storing block_num blocks of block_size size*/
	
	allocated_space = malloc(suggested_size - 1);
	memory_pool = FSAInit(allocated_space, suggested_size - 1, block_size);
	actual_block_num = FSACountFree(memory_pool);
	
	if (actual_block_num == block_num)
	{
		AddFailedTest("TestFSASuggestSize2\n");
		free(allocated_space);
		return 1;
	}
	
	free(allocated_space);
	return 0;
}

static int TestFSAAlloc(void)
{
	size_t suggested_size = 0;
	void *allocated_space = NULL;
	fsa_t *memory_pool = NULL;
	size_t block_size = 200;
	size_t block_num = 8;
	size_t actual_block_num = 0;
	size_t *elements[8] = {NULL};
	size_t *block = NULL;
	size_t loop_count = 0;
	size_t inside_loop_count = 0;
	
	suggested_size = FSASuggestSize(block_size, block_num);
	allocated_space = malloc(suggested_size);
	
	memory_pool = FSAInit(allocated_space, suggested_size, block_size);
	actual_block_num = FSACountFree(memory_pool);
	
	while(loop_count < actual_block_num)
	{
		elements[loop_count] = (size_t *)FSAAlloc(memory_pool);
		++loop_count;
	}
	
	
	/* checks if FSAAlloc succeded allocating all blocks*/
	loop_count = 0;
	while(loop_count < actual_block_num)
	{
		if (!elements[loop_count])
		{
			AddFailedTest("TestFSAAlloc1\n");
			free(allocated_space);
			return 1;
		}
		++loop_count;
	}
	
	/* checks if FSAAlloc allocated different address each time*/
	loop_count = 0;
	while(loop_count < actual_block_num)
	{
		inside_loop_count = loop_count + 1;
		while(inside_loop_count < actual_block_num)
		{
			if (elements[loop_count] == elements[inside_loop_count])
			{
				AddFailedTest("TestFSAAlloc2\n");
				free(allocated_space);
				return 1;
			}
			++inside_loop_count;
		}
		++loop_count;
	}
	
	/* checks if FSAAlloc doesn't allocate when there is no free space*/
	block = (size_t *)FSAAlloc(memory_pool);
	if (block)
	{
		AddFailedTest("TestFSAAlloc3\n");
		free(allocated_space);
		return 1;
	}
	
	free(allocated_space);
	return 0;
}


static int TestFSAFree(void)
{
	size_t suggested_size = 0;
	void *allocated_space = NULL;
	fsa_t *memory_pool = NULL;
	size_t block_size = 200;
	size_t block_num = 8;
	size_t actual_block_num = 0;
	size_t *elements[8] = {NULL};
	size_t *block = NULL;
	size_t loop_count = 0;
	
	suggested_size = FSASuggestSize(block_size, block_num);
	allocated_space = malloc(suggested_size);
	
	memory_pool = FSAInit(allocated_space, suggested_size, block_size);
	actual_block_num = FSACountFree(memory_pool);
	
	while(loop_count < actual_block_num)
	{
		elements[loop_count] = (size_t *)FSAAlloc(memory_pool);
		++loop_count;
	}
	
	/* checks if FSAFree actually frees the block*/
	FSAFree(memory_pool, elements[0]);
	
	block = (size_t *)FSAAlloc(memory_pool);
	if (!block)
	{
		AddFailedTest("TestFSAFree\n");
		free(allocated_space);
		return 1;
	}
	
	
	free(allocated_space);
	return 0;
}


static int TestFSACountFree(void)
{
	size_t suggested_size = 0;
	void *allocated_space = NULL;
	fsa_t *memory_pool = NULL;
	size_t block_size = 200;
	size_t block_num = 8;
	size_t actual_block_num = 0;
	size_t get_free_blocks_num = 0;
	size_t *elements[8] = {NULL};
	size_t loop_count = 0;
	
	suggested_size = FSASuggestSize(block_size, block_num);
	allocated_space = malloc(suggested_size);
	
	memory_pool = FSAInit(allocated_space, suggested_size, block_size);
	actual_block_num = FSACountFree(memory_pool);
	
	
	/* checks if FSAAlloc decreases FSACountFree by 1 each time until 0*/
	while(loop_count < actual_block_num)
	{
		elements[loop_count] = (size_t *)FSAAlloc(memory_pool);
		++loop_count;
		get_free_blocks_num = FSACountFree(memory_pool);
		if (get_free_blocks_num + loop_count != actual_block_num)
		{
			AddFailedTest("TestFSACountFree1\n");
			free(allocated_space);
			return 1;
		}
	}
	
	/* checks if FSAFree increases FSACountFree by 1 each time until block_num*/
	loop_count = 0;
	while(loop_count < actual_block_num)
	{
		FSAFree(memory_pool, elements[loop_count]);
		++loop_count;
		get_free_blocks_num = FSACountFree(memory_pool);
		if (get_free_blocks_num != loop_count)
		{
			AddFailedTest("TestFSACountFree2\n");
			free(allocated_space);
			return 1;
		}
	}
	
	
	free(allocated_space);
	return 0;
}

