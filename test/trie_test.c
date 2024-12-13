#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <stdlib.h> /* free() */
#include <assert.h>

#include "trie.h"

#define TESTNUM 4
#define DEPTH 6

static char failed_tests_print[300] = {'\0'};

static void AddFailedTest(const char *str);

static int TestInsert(void);
static int TestRemove(void);
static int TestCount(void);
static int TestFind(void);

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestInsert();
	printf("Tested Insert\n");

	failed_tests_num += TestRemove();
	printf("Tested Remove\n");

	failed_tests_num += TestCount();
	printf("Tested Count\n");

	/*failed_tests_num += TestFind();
	printf("Tested Find\n");*/

	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}

static void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}

static int TestInsert(void)
{
	trie_t *trie = NULL;
	trie_status_e status = TRIE_SUCCESS;
	int get_element = 0;
	size_t count = 0;
	
	/*create trie*/
	trie = TrieCreate(DEPTH);
	
	/* check if TRIE_SUCCESSfully inserted the requested key*/
	status = TrieInsert(trie, 0, &get_element);
	count = TrieCount(trie);
	if (1 != count || 0 != get_element || TRIE_SUCCESS != status)
	{
		AddFailedTest("TestInsert1\n");
		TrieDestroy(trie);
		return 1;
	}
	/* check if TRIE_SUCCESSfully inserted the requested key*/
	status = TrieInsert(trie, 63, &get_element);
	count = TrieCount(trie);
	if (2 != count || 63 != get_element || TRIE_SUCCESS != status)
	{
		printf(" count %ld ,element %d \n", count , get_element);
		AddFailedTest("TestInsert2\n");
		TrieDestroy(trie);
		return 1;
	}
	/* check if TRIE_SUCCESSfully inserted the requested key*/
	status = TrieInsert(trie, 62, &get_element);
	count = TrieCount(trie);
	if (3 != count || 62 != get_element || TRIE_SUCCESS != status)
	{
		printf(" count %ld ,element %d \n", count , get_element);
		AddFailedTest("TestInsert3\n");
		TrieDestroy(trie);
		return 1;
	}
	/* check if TRIE_SUCCESSfully inserted even when the key is taken*/
	status = TrieInsert(trie, get_element, &get_element);
	count = TrieCount(trie);
	if (4 != count || TRIE_SUCCESS != status || 1 != get_element)
	{
		printf(" count %ld ,element %d \n", count , get_element);
		AddFailedTest("TestInsert4\n");
		TrieDestroy(trie);
		return 1;
	}
	/* check if TRIE_SUCCESSfully inserted the requested key*/
	status = TrieInsert(trie, 40, &get_element);
	count = TrieCount(trie);
	if (5 != count || TRIE_SUCCESS != status)
	{
		AddFailedTest("TestInsert5\n");
		TrieDestroy(trie);
		return 1;
	}
	
	status = TrieInsert(trie, 40, &get_element);
	count = TrieCount(trie);
	if (6 != count || TRIE_SUCCESS != status || 41 != get_element)
	{
	
				printf(" count %ld ,element %d \n", count , get_element);
		AddFailedTest("TestInsert8\n");
		TrieDestroy(trie);
		return 1;
	}
	
	/* check if existing keys can be found*/
	/*status = TrieFind(trie, 41);
	if (TRIE_SUCCESS != status)
	{
		AddFailedTest("TestInsert9\n");
		TrieDestroy(trie);
		return 1;
	}
	*/
	status = TrieInsert(trie, 53, &get_element);
	count = TrieCount(trie);
	if (7 != count || TRIE_SUCCESS != status || 53 != get_element)
	{
		AddFailedTest("TestInsert10\n");
		TrieDestroy(trie);
		return 1;
	}
	
	status = TrieInsert(trie, 53, &get_element);
	count = TrieCount(trie);
	if (8 != count || TRIE_SUCCESS != status || 54 != get_element)
	{
		AddFailedTest("TestInsert11\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieDestroy(trie);
	return 0;
}

static int TestRemove(void)
{
	trie_t *trie = NULL;
	trie_status_e status = TRIE_SUCCESS;
	int get_element = 0;
	size_t count = 0;
	
	/*create trie*/
	trie = TrieCreate(DEPTH);
	
	TrieInsert(trie, 0, &get_element);
	TrieInsert(trie, 63, &get_element);
	TrieInsert(trie, 62, &get_element);
	TrieInsert(trie, 40, &get_element);
	
	/* check if TRIE_SUCCESSfully removed the requested key*/
	status = TrieRemove(trie, get_element);
	count = TrieCount(trie);
	if (3 != count || TRIE_SUCCESS != status)
	{
		AddFailedTest("TestRemove1\n");
		TrieDestroy(trie);
		return 1;
	}
	
	
	
	/* check if TRIE_SUCCESSfully removed the requested key*/
	status = TrieRemove(trie, 63);
	count = TrieCount(trie);
	if (2 != count || TRIE_SUCCESS != status)
	{
		AddFailedTest("TestRemove3\n");
		TrieDestroy(trie);
		return 1;
	}
	
	
	
	/* check if previously removed key can be inserted*/
	TrieInsert(trie, 63, &get_element);
	count = TrieCount(trie);
	if (3 != count || 63 != get_element)
	{
		AddFailedTest("TestRemove5\n");
		TrieDestroy(trie);
		return 1;
	}
	
	/* check if remove updates ancestors fullness */
	TrieInsert(trie, 61, &get_element);
	TrieInsert(trie, 60, &get_element);
	TrieInsert(trie, 59, &get_element);
	TrieInsert(trie, 58, &get_element);
	TrieInsert(trie, 57, &get_element);
	TrieInsert(trie, 56, &get_element);
	
	status = TrieRemove(trie, 63);
	count = TrieCount(trie);
	if (8 != count || TRIE_SUCCESS != status)
	{
		AddFailedTest("TestRemove6\n");
		TrieDestroy(trie);
		return 1;
	}
	
	
	TrieDestroy(trie);
	return 0;
}


static int TestCount(void)
{
	trie_t *trie = NULL;
	int get_element = 0;
	size_t count = 0;
	
	/*create trie*/
	trie = TrieCreate(DEPTH);
	count = TrieCount(trie);
	if (0 != count)
	{
		printf("%ld \n", count);
		AddFailedTest("TestCount1\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieInsert(trie, 0, &get_element);
	count = TrieCount(trie);
	if (1 != count)
	{
		AddFailedTest("TestCount2\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieInsert(trie, 63, &get_element);
	count = TrieCount(trie);
	if (2 != count)
	{
		AddFailedTest("TestCount3\n");
		TrieDestroy(trie);
		return 1;
	}
	TrieInsert(trie, 62, &get_element);
	count = TrieCount(trie);
	if (3 != count)
	{
		AddFailedTest("TestCount4\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieInsert(trie, 40, &get_element);
	count = TrieCount(trie);
	if (4 != count)
	{
		AddFailedTest("TestCount5\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieRemove(trie, 63);
	count = TrieCount(trie);
	if (3 != count)
	{
		AddFailedTest("TestCount6\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieRemove(trie, 62);
	count = TrieCount(trie);
	if (2 != count)
	{
		AddFailedTest("TestCount7\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieRemove(trie, 0);
	count = TrieCount(trie);
	if (1 != count)
	{
		AddFailedTest("TestCount8\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieRemove(trie, 40);
	count = TrieCount(trie);
	if (0 != count)
	{
		AddFailedTest("TestCount9\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieDestroy(trie);
	return 0;
}
/*
static int TestFind(void)
{
	trie_t *trie = NULL;
	trie_status_e status = TRIE_SUCCESS;
	int get_element = 0;
	size_t count = 0;*/
	
	/*create trie*/
	/*trie = TrieCreate(DEPTH);

	status = TrieFind(trie, 0);
	if (NOT_FOUND != status)
	{
		AddFailedTest("TestFind1\n");
		TrieDestroy(trie);
		return 1;
	}*/
	
	/* check if existing keys can be found*/
	/*TrieInsert(trie, 0, &get_element);
	status = TrieFind(trie, 0);
	if (TRIE_SUCCESS != status)
	{
		AddFailedTest("TestFind2\n");
		TrieDestroy(trie);
		return 1;
	}
	
	TrieInsert(trie, 63, &get_element);
	status = TrieFind(trie, get_element);
	if (TRIE_SUCCESS != status)
	{
		AddFailedTest("TestFind3\n");
		TrieDestroy(trie);
		return 1;
	}*/
	
	/* check if non-existing keys cannot be found*/
	/*status = TrieFind(trie, 40);
	if (NOT_FOUND != status)
	{
		AddFailedTest("TestFind4\n");
		TrieDestroy(trie);
		return 1;
	}*/
	
	/* check if removed keys cannot be found*/
	/*TrieRemove(trie, 63);
	status = TrieFind(trie, 63);
	if (NOT_FOUND != status)
	{
		AddFailedTest("TestFind5\n");
		TrieDestroy(trie);
		return 1;
	}

	
	TrieDestroy(trie);
	return 0;
}*/

