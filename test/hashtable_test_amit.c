#include <stdio.h> /* printf() */
#include <stdlib.h> /* rand(), srand() */
#include <time.h> /* time() */
#include <string.h>  /* strcat() */

#include "hashtable.h"

#define TESTNUM 7
#define MAX_NAME_LENGTH 30
#define MAX_MEOW_LENGTH 20
#define HASH_TABLE_SIZE 16
#define BIG_HASH_TABLE_SIZE 3000
#define NUM_OF_CATS 20
#define MAX_WORDS 200000
#define MAX_STR_LENGTH 25

static char failed_tests_print[300] = {'\0'};

static void AddFailedTest(const char *str);

static int TestInsert(void);
static int TestRemove(void);
static int TestSize(void);

static int TestForEach(void);
static int TestIsEmpty(void);
static int TestFind(void);

static size_t next_id = 100000000;

typedef struct cat
{
	char name[MAX_NAME_LENGTH];
	char meow[MAX_MEOW_LENGTH];
	int age;
	size_t id;
} cat_t;

size_t CatHashFunction(const void *key);
size_t Fold(size_t id);
static void GenerateCatArray(cat_t cats[], size_t num_cats);
int IsSameCat(const void *key1, const void *key2);
int CatsHadBirthday(void *data, void *params);
int IsSameString(const void *key1, const void *key2);
size_t StringHashFunction(const void *key);

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestInsert();
	printf("Tested Insert\n");
	failed_tests_num += TestRemove();
	printf("Tested Remove\n");
	failed_tests_num += TestSize();
	printf("Tested Size\n");
	
	failed_tests_num += TestForEach();
	printf("Tested ForEach\n");
	failed_tests_num += TestIsEmpty();
	printf("Tested IsEmpty\n");
	failed_tests_num += TestFind();
	printf("Tested Find\n");
	
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
	hash_table_t *table = HashTableCreate(CatHashFunction, IsSameCat, HASH_TABLE_SIZE);
	cat_t cats[NUM_OF_CATS] = {{0}};
	size_t loop_count = 0;
	int status = 0;
	cat_t *find_cat = NULL;
	
	GenerateCatArray(cats, NUM_OF_CATS);
	
	for (loop_count = 0; 0 == status && loop_count < NUM_OF_CATS; ++loop_count) 
	{
		status = HashTableInsert(table, cats+loop_count, cats+loop_count);
	}
	
	if (0 != status)
	{
		AddFailedTest("TestInsert1\n");
		HashTableDestroy(table);
		return 1;
	}
	
	find_cat = (cat_t *)HashTableFind(table, cats+11);
	
	if (!IsSameCat(find_cat, cats+11))
	{
		AddFailedTest("TestInsert2\n");
		HashTableDestroy(table);
		return 1;
	}
	
	if (NUM_OF_CATS != HashTableSize(table))
	{
		AddFailedTest("TestInsert3\n");
		HashTableDestroy(table);
		return 1;
	}
	
	HashTableDestroy(table);
	return 0;
}

static int TestRemove(void)
{
	hash_table_t *table = HashTableCreate(CatHashFunction, IsSameCat, HASH_TABLE_SIZE);
	cat_t cats[NUM_OF_CATS] = {{0}};
	size_t loop_count = 0;
	cat_t *find_cat = NULL;
	
	GenerateCatArray(cats, NUM_OF_CATS);
	
	for (loop_count = 0; loop_count < NUM_OF_CATS; ++loop_count) 
	{
		HashTableInsert(table, cats+loop_count, cats+loop_count);
	}
	
	for (loop_count = 0; loop_count < NUM_OF_CATS; ++loop_count) 
	{
		HashTableRemove(table, cats+loop_count);
		if (NUM_OF_CATS - 1 != HashTableSize(table) + loop_count)
		{
			AddFailedTest("TestRemove\n");
			HashTableDestroy(table);
			return 1;
		}
	}
	
	
	HashTableDestroy(table);
	return 0;
}

static int TestSize(void)
{
	hash_table_t *table = HashTableCreate(CatHashFunction, IsSameCat, HASH_TABLE_SIZE);
	cat_t cats[NUM_OF_CATS] = {{0}};
	size_t loop_count = 0;
	cat_t *find_cat = NULL;
	
	GenerateCatArray(cats, NUM_OF_CATS);
	
	for (loop_count = 0; loop_count < NUM_OF_CATS; ++loop_count) 
	{
		HashTableInsert(table, cats+loop_count, cats+loop_count);
		if (loop_count + 1 != HashTableSize(table))
		{
			AddFailedTest("TestSize1\n");
			HashTableDestroy(table);
			return 1;
		}
	}
	
	for (loop_count = 0; loop_count < NUM_OF_CATS; ++loop_count) 
	{
		HashTableRemove(table, cats+loop_count);
		if (NUM_OF_CATS - 1 != HashTableSize(table) + loop_count)
		{
			AddFailedTest("TestSize2\n");
			HashTableDestroy(table);
			return 1;
		}
	}
	
	HashTableDestroy(table);
	return 0;
}

static int TestForEach(void)
{
	hash_table_t *table = HashTableCreate(CatHashFunction, IsSameCat, HASH_TABLE_SIZE);
	cat_t cats[NUM_OF_CATS] = {{0}};
	size_t loop_count = 0;
	cat_t *find_cat = NULL;
	cat_t sixth_cat = {0};
	cat_t eleventh_cat = {0};
	int sixth_cat_age = 0;
	int eleventh_cat_age = 0;
	
	GenerateCatArray(cats, NUM_OF_CATS);
	
	for (loop_count = 0; loop_count < 10; ++loop_count) 
	{
		HashTableInsert(table, cats+loop_count, cats+loop_count);
	}
	
	sixth_cat = cats[6];
	eleventh_cat = cats[11];
	
	sixth_cat_age = sixth_cat.age;
	eleventh_cat_age = eleventh_cat.age;
	
	HashTableForEach(table, CatsHadBirthday, &sixth_cat);
	
	sixth_cat = *(cat_t *)HashTableFind(table, cats+6);
	
	if (sixth_cat_age + 1 != sixth_cat.age)
	{
		AddFailedTest("TestForEach1\n");
		HashTableDestroy(table);
		return 1;
	}
	
	if (eleventh_cat_age != cats[11].age)
	{
		AddFailedTest("TestForEach2\n");
		HashTableDestroy(table);
		return 1;
	}
	
	HashTableDestroy(table);
	return 0;
}

static int TestIsEmpty(void)
{
	hash_table_t *table = HashTableCreate(CatHashFunction, IsSameCat, HASH_TABLE_SIZE);
	cat_t cats[NUM_OF_CATS] = {{0}};
	cat_t *find_cat = NULL;
	
	GenerateCatArray(cats, NUM_OF_CATS);
	
	if (!HashTableIsEmpty(table))
	{
		AddFailedTest("TestIsEmpty\n");
		HashTableDestroy(table);
		return 1;
	}
	
	HashTableInsert(table, cats, cats);
	
	if (HashTableIsEmpty(table))
	{
		AddFailedTest("TestIsEmpty\n");
		HashTableDestroy(table);
		return 1;
	}
	
	HashTableInsert(table, cats+1, cats+1);
	
	if (HashTableIsEmpty(table))
	{
		AddFailedTest("TestIsEmpty\n");
		HashTableDestroy(table);
		return 1;
	}
	
	HashTableRemove(table, cats);
	
	if (HashTableIsEmpty(table))
	{
		AddFailedTest("TestIsEmpty\n");
		HashTableDestroy(table);
		return 1;
	}
	
	HashTableRemove(table, cats+1);
	
	if (!HashTableIsEmpty(table))
	{
		AddFailedTest("TestIsEmpty\n");
		HashTableDestroy(table);
		return 1;
	}
	
	
	HashTableDestroy(table);
	return 0;
}

static int TestFind(void)
{
	hash_table_t *table = HashTableCreate(CatHashFunction, IsSameCat, HASH_TABLE_SIZE);
	cat_t cats[NUM_OF_CATS] = {{0}};
	size_t loop_count = 0;
	cat_t find_cat = {0};
	cat_t sixth_cat = {0};
	cat_t eleventh_cat = {0};

	
	GenerateCatArray(cats, NUM_OF_CATS);
	
	for (loop_count = 0; loop_count < 10; ++loop_count) 
	{
		HashTableInsert(table, cats+loop_count, cats+loop_count);
	}
	
	sixth_cat = cats[6];
	eleventh_cat = cats[11];
	
	find_cat = *(cat_t *)HashTableFind(table, cats+6);
	if (!IsSameCat(&find_cat, &sixth_cat))
	{
		AddFailedTest("TestFind1\n");
		HashTableDestroy(table);
		return 1;
	}
	
	if (HashTableFind(table, cats+11))
	{
		AddFailedTest("TestFind2\n");
		HashTableDestroy(table);
		return 1;
	}
	
	HashTableDestroy(table);
	return 0;
}


int CatsHadBirthday(void *data, void *params)
{
	cat_t *cat = (cat_t *)data;
	(void)params;
	
	++(cat->age);
	return 0;
}


size_t CatHashFunction(const void *key)
{
	cat_t cat = *(cat_t *)key;
	
	return (Fold(cat.id) % HASH_TABLE_SIZE);
}


size_t Fold(size_t id)
{
	size_t fold_result = 0;
	while (id > 0)
	{
		fold_result += id%1000;
		id /= 1000;
	}
	
	return fold_result;
}


int IsSameCat(const void *key1, const void *key2)
{
	cat_t cat1 = *(cat_t *)key1;
	cat_t cat2 = *(cat_t *)key2;
	
	return (cat1.id == cat2.id);
}


static void GenerateCatArray(cat_t cats[], size_t num_cats) 
{
	size_t i = 0;
	char *name = NULL;
	char *meow = NULL;
	int age = 0;
	
	char *names[] = 
	{
		"Mr. Fluffington", "Sir Meowsalot", "Princess Snugglepants",
		"Lord Whiskerbottom", "Baron von Purrington", "Countess Pounce-a-lot",
		"Duchess Fuzzypaws", "Emperor Mewington", "Captain Snickerdoodle", 
		"Lady Jellybean", "Sir Fuzzington", "Madame Fluffernutter",
		"Colonel Purrberry", "Queen Cupcake", "General Pawsome", 
		"Sir Snugglebug", "Lady Waffles", "Sir Fuzzyface", 
		"Baroness Cuddlefluff", "Princess Muffintop"
	};

	char *meows[] = 
	{
		"meow", "purr", "mew", "meep", "nya",
		"fluffpuff", "moop", "wampus", "purrrrrr", "BAJUBUJONIT",
		"meowch", "merp", "plup", "chupuchupu"
	};

	srand((unsigned int)time(NULL));

	for (i = 0; i < num_cats; ++i) 
	{
		name = names[i % (sizeof(names) / sizeof(names[0]))];
		meow = meows[i % (sizeof(meows) / sizeof(meows[0]))];
		age = rand() % 50 + 1;
		
		cats[i].id = next_id++;

		strncpy(cats[i].name, name, MAX_NAME_LENGTH - 1);
		cats[i].name[MAX_NAME_LENGTH - 1] = '\0';
		strncpy(cats[i].meow, meow, MAX_MEOW_LENGTH - 1);
		cats[i].meow[MAX_MEOW_LENGTH - 1] = '\0';
		cats[i].age = age;
	}
}

