#include <stdio.h> /* printf */
#include <string.h> /*strcmp */

#include "hashtable.h"

#define NUM_OF_BUCKETS 720

typedef struct person
{
	char *name;
	char *job;
	int age;
	int id;
}person_t;

size_t HashFunction(const void *key);
int Add1ToAge(void *data, void *params);
size_t FourIndexHashFunction(const void *key);
int HashCmpFunc(const void *key1, const void *key2);
size_t OneIndexHashFunction(const void *key);

static void TestInsertFind(void);
static void TestSizeEmpty(void);
static void TestRemove(void);
static void TestForEach(void);
static void TestCache(void);
static void TestHashTableLoad(void);
static void TestStddev(void);

static size_t checker = 0;

int main(void)
{
	TestSizeEmpty();
	TestInsertFind();
	TestRemove();
	TestForEach();
	TestCache();
	TestHashTableLoad();
	TestStddev();
	
	if(0 == checker)
	{
		printf("\nALL TESTS PASSED!\n");
	}
	
	return 0;
}

int HashCmpFunc(const void *key1, const void *key2)
{
	person_t person = *(person_t *)key1;
	
	return person.id == *(int *)key2;
}

int Add1ToAge(void *data, void *params)
{
	(void)params;
	((person_t *)data)->age += 1;
	
	return 0;
}

int PrintTableNames(void *data, void *params)
{
	(void)params;
	printf("%s ->", ((person_t *)data)->name);
	
	return 0;
}

size_t HashFunction(const void *key)
{
	int id = *(int *)key;
	
    return id % NUM_OF_BUCKETS;
}

size_t FourIndexHashFunction(const void *key)
{
	int id = *(int *)key;
	
    return id % 4;
}

size_t OneIndexHashFunction(const void *key)
{
	(void)key;
	
    return 0;
}


static void TestSizeEmpty(void)
{
	hash_table_t *hash = HashTableCreate(HashFunction, HashCmpFunc, NUM_OF_BUCKETS);
	person_t Aviad = {"Aviad Caduri", "Plumber", 76, 287121};
	person_t Avi = {"Avi Levi", "Cleaner", 11, 282711};
	person_t Avia = {"Avia David", "Carpenter", 13, 99887};
	person_t Eli = {"Eli Levi", "Musician", 89, 1726151};
	person_t Oran = {"Oran Levi", "Office manager", 73, 65541};
	person_t Ofir = {"Ofir Levi", "Constructor", 71, 111162};
	person_t Yarin = {"Yarin Levi", "Finance", 33, 1542};
	
	if(0 == HashTableSize(hash) && 1 == HashTableIsEmpty(hash))
	{
		printf("Test HashTableSize 1 passed!\n");
		printf("Test HashTableIsEmpty 1 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableSize 1 failed!\n");
		printf("Test HashTableIsEmpty 1 failed!\n");
	}
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	if(1 == HashTableSize(hash) && 0 == HashTableIsEmpty(hash))
	{
		printf("Test HashTableSize 2 passed!\n");
		printf("Test HashTableIsEmpty 2 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableSize 2 failed!\n");
		printf("Test HashTableIsEmpty 2 failed!\n");
	}
	
	HashTableInsert(hash, &Avi.id, &Avi);
	if(2 == HashTableSize(hash) && 0 == HashTableIsEmpty(hash))
	{
		printf("Test HashTableSize 3 passed!\n");
		printf("Test HashTableIsEmpty 3 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableSize 3 failed!\n");
		printf("Test HashTableIsEmpty 3 failed!\n");
	}
	
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	if(4 == HashTableSize(hash) && 0 == HashTableIsEmpty(hash))
	{
		printf("Test HashTableSize 4 passed!\n");
		printf("Test HashTableIsEmpty 4 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableSize 4 failed!\n");
		printf("Test HashTableIsEmpty 4 failed!\n");
	}
	
	HashTableInsert(hash, &Oran.id, &Oran);
	HashTableInsert(hash, &Ofir.id, &Ofir);
	if(6 == HashTableSize(hash) && 0 == HashTableIsEmpty(hash))
	{
		printf("Test HashTableSize 5 passed!\n");
		printf("Test HashTableIsEmpty 5 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableSize 5 failed!\n");
		printf("Test HashTableIsEmpty 5 failed!\n");
	}
	
	HashTableInsert(hash, &Yarin.id, &Yarin);
	if(7 == HashTableSize(hash) && 0 == HashTableIsEmpty(hash))
	{
		printf("Test HashTableSize 6 passed!\n");
		printf("Test HashTableIsEmpty 6 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableSize 6 failed!\n");
		printf("Test HashTableIsEmpty 6 failed!\n");
	}
	
	HashTableRemove(hash, &Yarin.id);
	HashTableRemove(hash, &Oran.id);
	if(5 == HashTableSize(hash) && 0 == HashTableIsEmpty(hash))
	{
		printf("Test HashTableSize 7 passed!\n");
		printf("Test HashTableIsEmpty 7 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableSize 7 failed!\n");
		printf("Test HashTableIsEmpty 7 failed!\n");
	}
	
	HashTableRemove(hash, &Ofir.id);
	HashTableRemove(hash, &Eli.id);
	HashTableRemove(hash, &Avi.id);
	HashTableRemove(hash, &Avia.id);
	HashTableRemove(hash, &Aviad.id);
	if(0 == HashTableSize(hash) && 1 == HashTableIsEmpty(hash))
	{
		printf("Test HashTableSize 8 passed!\n");
		printf("Test HashTableIsEmpty 8 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableSize 8 failed!\n");
		printf("Test HashTableIsEmpty 8 failed!\n");
	}
	
	HashTableDestroy(hash);
}


static void TestInsertFind(void)
{
	hash_table_t *hash = HashTableCreate(HashFunction, HashCmpFunc, NUM_OF_BUCKETS);
	person_t *finder = NULL;
	
	person_t Aviad = {"Aviad Caduri", "Plumber", 76, 287121};
	person_t Avi = {"Avi Levi", "Cleaner", 11, 282711};
	person_t Avia = {"Avia David", "Carpenter", 13, 99887};
	person_t Eli = {"Eli Levi", "Musician", 89, 1726151};
	person_t Eti = {"Eti Levi", "Athlete", 54, 98101};
	person_t Oran = {"Oran Levi", "Office manager", 73, 65541};
	person_t Ofir = {"Ofir Levi", "Constructor", 71, 111162};
	person_t Yarin = {"Yarin Levi", "Finance", 33, 1542};
	person_t Timor = {"Timor Levi", "Finance", 18, 8817162};
	person_t Ella = {"Ella Levi", "Plumber", 20, 1133221};
	person_t Eliav = {"Eliav Levi", "Teacher", 22, 1212};
	person_t Aaron = {"Aaron Cohen", "A/C tech", 5, 980808};
	person_t Natan = {"Natan Cohen", "Soccer player", 67, 4565465};
	person_t Dor = {"Dor Cohen", "A/C tech", 55, 16524};
	person_t Amit = {"Amit Cohen", "Actor", 55, 8172};
	person_t Shahar = {"Shahar Cohen", "Mentor", 22, 111111};
	person_t Matan = {"Matan Cohen", "Handyman", 16, 198201};
	person_t Or = {"Or Cohen", "A/C tech", 27, 62514};
	person_t Ori = {"Ori Cohen", "Student", 26, 263541};
	person_t Oriah = {"Oriah Cohen", "Bussines", 45, 192827};
	person_t Alon = {"Alon Cohen", "Bussines", 44, 3335243};
	person_t Alona = {"Alona Cohen", "Student", 34, 2112221};
	person_t Dori = {"Dori Cohen", "Bussines", 61, 1298987};
	person_t Tom = {"Tom Cohen", "Student", 24, 777766};
	person_t Arik = {"Arik Cohen", "Bussines", 38, 100012};
	person_t Yan = {"Yan Meiri", "Bussines", 27, 2553434};
	
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	HashTableInsert(hash, &Avi.id, &Avi);
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	HashTableInsert(hash, &Oran.id, &Oran);
	HashTableInsert(hash, &Ofir.id, &Ofir);
	HashTableInsert(hash, &Yarin.id, &Yarin);
	HashTableInsert(hash, &Timor.id, &Timor);
	HashTableInsert(hash, &Ella.id, &Ella);
	HashTableInsert(hash, &Eliav.id, &Eliav);
	HashTableInsert(hash, &Shahar.id, &Shahar);
	HashTableInsert(hash, &Alon.id, &Alon);
	HashTableInsert(hash, &Alona.id, &Alona);
	HashTableInsert(hash, &Ori.id, &Ori);
	HashTableInsert(hash, &Dori.id, &Dori);
	HashTableInsert(hash, &Tom.id, &Tom);
	HashTableInsert(hash, &Arik.id, &Arik);
	HashTableInsert(hash, &Yan.id, &Yan);
	HashTableInsert(hash, &Matan.id, &Matan);
	HashTableInsert(hash, &Oriah.id, &Oriah);
	HashTableInsert(hash, &Or.id, &Or);
	HashTableInsert(hash, &Amit.id, &Amit);
	HashTableInsert(hash, &Natan.id, &Natan);
	HashTableInsert(hash, &Aaron.id, &Aaron);
	HashTableInsert(hash, &Eti.id, &Eti);
	HashTableInsert(hash, &Dor.id, &Dor);

	
	finder = (person_t *)HashTableFind(hash, &Aviad.id);
	if(finder->id == Aviad.id)
	{
		printf("Test HashTableInsert 1 passed!\n");
		printf("Test HashTableFind 1 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableInsert 1 failed!\n");
		printf("Test HashTableFind 1 failed!\n");
	}
	
	finder = (person_t *)HashTableFind(hash, &Dor.id);
	if(finder->id == Dor.id)
	{
		printf("Test HashTableInsert 2 passed!\n");
		printf("Test HashTableFind 2 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableInsert 2 failed!\n");
		printf("Test HashTableFind 2 failed!\n");
	}
	
	finder = (person_t *)HashTableFind(hash, &Oran.id);
	if(finder->id == Oran.id)
	{
		printf("Test HashTableInsert 3 passed!\n");
		printf("Test HashTableFind 3 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableInsert 3 failed!\n");
		printf("Test HashTableFind 3 failed!\n");
	}
	
	finder = (person_t *)HashTableFind(hash, &Yarin.id);
	if(finder->id == Yarin.id)
	{
		printf("Test HashTableInsert 4 passed!\n");
		printf("Test HashTableFind 4 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableInsert 4 failed!\n");
		printf("Test HashTableFind 4 failed!\n");
	}
	
	finder = (person_t *)HashTableFind(hash, &Tom.id);
	if(finder->id == Tom.id)
	{
		printf("Test HashTableInsert 5 passed!\n");
		printf("Test HashTableFind 5 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableInsert 5 failed!\n");
		printf("Test HashTableFind 5 failed!\n");
	}
	
	finder = (person_t *)HashTableFind(hash, &Ori.id);
	if(finder->id == Ori.id)
	{
		printf("Test HashTableInsert 6 passed!\n");
		printf("Test HashTableFind 6 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableInsert 6 failed!\n");
		printf("Test HashTableFind 6 failed!\n");
	}
	
	HashTableDestroy(hash);
}

static void TestRemove(void)
{
	hash_table_t *hash = HashTableCreate(HashFunction, HashCmpFunc, NUM_OF_BUCKETS);
	person_t *finder = NULL;
	
	person_t Aviad = {"Aviad Caduri", "Plumber", 76, 287121};
	person_t Avi = {"Avi Levi", "Cleaner", 11, 282711};
	person_t Avia = {"Avia David", "Carpenter", 13, 99887};
	person_t Eli = {"Eli Levi", "Musician", 89, 1726151};
	person_t Eti = {"Eti Levi", "Athlete", 54, 98101};
	person_t Oran = {"Oran Levi", "Office manager", 73, 65541};
	person_t Ofir = {"Ofir Levi", "Constructor", 71, 111162};
	person_t Yarin = {"Yarin Levi", "Finance", 33, 1542};
	person_t Timor = {"Timor Levi", "Finance", 18, 8817162};
	person_t Ella = {"Ella Levi", "Plumber", 20, 1133221};
	person_t Eliav = {"Eliav Levi", "Teacher", 22, 1212};
	person_t Aaron = {"Aaron Cohen", "A/C tech", 5, 980808};
	person_t Natan = {"Natan Cohen", "Soccer player", 67, 4565465};
	person_t Dor = {"Dor Cohen", "A/C tech", 55, 16524};
	person_t Amit = {"Amit Cohen", "Actor", 55, 8172};
	person_t Shahar = {"Shahar Cohen", "Mentor", 22, 111111};
	person_t Matan = {"Matan Cohen", "Handyman", 16, 198201};
	person_t Or = {"Or Cohen", "A/C tech", 27, 62514};
	person_t Ori = {"Ori Cohen", "Student", 26, 263541};
	person_t Oriah = {"Oriah Cohen", "Bussines", 45, 192827};
	person_t Alon = {"Alon Cohen", "Bussines", 44, 3335243};
	person_t Alona = {"Alona Cohen", "Student", 34, 2112221};
	person_t Dori = {"Dori Cohen", "Bussines", 61, 1298987};
	person_t Tom = {"Tom Cohen", "Student", 24, 777766};
	person_t Arik = {"Arik Cohen", "Bussines", 38, 100012};
	person_t Yan = {"Yan Meiri", "Bussines", 27, 2553434};
	
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	HashTableInsert(hash, &Avi.id, &Avi);
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	HashTableInsert(hash, &Oran.id, &Oran);
	HashTableInsert(hash, &Ofir.id, &Ofir);
	HashTableInsert(hash, &Yarin.id, &Yarin);
	HashTableInsert(hash, &Timor.id, &Timor);
	HashTableInsert(hash, &Ella.id, &Ella);
	HashTableInsert(hash, &Eliav.id, &Eliav);
	HashTableInsert(hash, &Shahar.id, &Shahar);
	HashTableInsert(hash, &Alon.id, &Alon);
	HashTableInsert(hash, &Alona.id, &Alona);
	HashTableInsert(hash, &Ori.id, &Ori);
	HashTableInsert(hash, &Dori.id, &Dori);
	HashTableInsert(hash, &Tom.id, &Tom);
	HashTableInsert(hash, &Arik.id, &Arik);
	HashTableInsert(hash, &Yan.id, &Yan);
	HashTableInsert(hash, &Matan.id, &Matan);
	HashTableInsert(hash, &Oriah.id, &Oriah);
	HashTableInsert(hash, &Or.id, &Or);
	HashTableInsert(hash, &Amit.id, &Amit);
	HashTableInsert(hash, &Natan.id, &Natan);
	HashTableInsert(hash, &Aaron.id, &Aaron);
	HashTableInsert(hash, &Eti.id, &Eti);
	HashTableInsert(hash, &Dor.id, &Dor);
	
	
	
	HashTableRemove(hash, &Ofir.id);
	HashTableRemove(hash, &Eli.id);
	HashTableRemove(hash, &Avi.id);
	HashTableRemove(hash, &Avia.id);
	HashTableRemove(hash, &Aviad.id);
	finder = (person_t *)HashTableFind(hash, &Avia.id);
	if(21 == HashTableSize(hash) && NULL == finder)
	{
		printf("Test HashTableRemove 1 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableRemove 1 failed!\n");
	}
	
	
	HashTableRemove(hash, &Or.id);
	HashTableRemove(hash, &Ori.id);
	HashTableRemove(hash, &Oriah.id);
	HashTableRemove(hash, &Eti.id);
	HashTableRemove(hash, &Arik.id);
	finder = (person_t *)HashTableFind(hash, &Arik.id);
	if(16 == HashTableSize(hash) && NULL == finder)
	{
		printf("Test HashTableRemove 2 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableRemove 2 failed!\n");
	}
	
	HashTableDestroy(hash);
}


static void TestForEach(void)
{
	hash_table_t *hash = HashTableCreate(HashFunction, HashCmpFunc, NUM_OF_BUCKETS);
	person_t *finder = NULL;
	int status = 0;
	
	
	person_t Aviad = {"Aviad Caduri", "Plumber", 76, 287121};
	person_t Avi = {"Avi Levi", "Cleaner", 11, 282711};
	person_t Avia = {"Avia David", "Carpenter", 13, 99887};
	person_t Eli = {"Eli Levi", "Musician", 89, 1726151};
	person_t Eti = {"Eti Levi", "Athlete", 54, 98101};
	person_t Oran = {"Oran Levi", "Office manager", 73, 65541};
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	HashTableInsert(hash, &Avi.id, &Avi);
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	HashTableInsert(hash, &Eti.id, &Eti);
	HashTableInsert(hash, &Oran.id, &Oran);
	
	status = HashTableForEach(hash, Add1ToAge, NULL);
	finder = (person_t *)HashTableFind(hash, &Aviad.id);
	if(77 == finder->age && 0 == status)
	{
		printf("Test HashTableForEach 1 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableForEach 1 failed!\n");
	}
	
	finder = (person_t *)HashTableFind(hash, &Avi.id);
	if(12 == finder->age)
	{
		printf("Test HashTableForEach 2 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableForEach 2 failed!\n");
	}
	
	finder = (person_t *)HashTableFind(hash, &Avia.id);
	if(14 == finder->age)
	{
		printf("Test HashTableForEach 3 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableForEach 3 failed!\n");
	}
	
	finder = (person_t *)HashTableFind(hash, &Oran.id);
	if(74 == finder->age)
	{
		printf("Test HashTableForEach 4 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableForEach 4 failed!\n");
	}
	
	HashTableDestroy(hash);
}

static void TestCache(void)
{
	hash_table_t *hash = HashTableCreate(OneIndexHashFunction, HashCmpFunc, 1);
	person_t *finder = NULL;
	
	person_t Aviad = {"Aviad Caduri", "Plumber", 76, 287121};
	person_t Avi = {"Avi Levi", "Cleaner", 11, 282711};
	person_t Avia = {"Avia David", "Carpenter", 13, 99887};
	person_t Eli = {"Eli Levi", "Musician", 89, 1726151};
	person_t Eti = {"Eti Levi", "Athlete", 54, 98101};
	person_t Oran = {"Oran Levi", "Office manager", 73, 65541};
	
	printf("\nTest Cache:\n");
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	HashTableInsert(hash, &Avi.id, &Avi);
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	HashTableInsert(hash, &Eti.id, &Eti);
	HashTableInsert(hash, &Oran.id, &Oran);
	
	printf("Printing table: ");
	HashTableForEach(hash, PrintTableNames, NULL);
	printf("\n");
	
	finder = (person_t *)HashTableFind(hash, &Avi.id);
	printf("Printing bucket after finding Avi: ");
	HashTableForEach(hash, PrintTableNames, NULL);
	printf("\n");
	
	finder = (person_t *)HashTableFind(hash, &Avia.id);
	printf("Printing bucket after finding Avia: ");
	HashTableForEach(hash, PrintTableNames, NULL);
	printf("\n");
	
	finder = (person_t *)HashTableFind(hash, &Oran.id);
	printf("Printing bucket after finding Oran: ");
	HashTableForEach(hash, PrintTableNames, NULL);
	printf("\n\n");
	
	(void)finder;
	HashTableDestroy(hash);
}

static void TestHashTableLoad(void)
{	
	hash_table_t *hash = HashTableCreate(HashFunction, HashCmpFunc, NUM_OF_BUCKETS);
	
	person_t Aviad = {"Aviad Caduri", "Plumber", 76, 287121};
	person_t Avi = {"Avi Levi", "Cleaner", 11, 282711};
	person_t Avia = {"Avia David", "Carpenter", 13, 99887};
	person_t Eli = {"Eli Levi", "Musician", 89, 1726151};
	person_t Eti = {"Eti Levi", "Athlete", 54, 98101};
	person_t Oran = {"Oran Levi", "Office manager", 73, 65541};
	
	if(0 == HashTableLoad(hash))
	{
		printf("Test HashTableLoad 1 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableLoad 1 failed!\n");
	}
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	HashTableInsert(hash, &Avi.id, &Avi);
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	HashTableInsert(hash, &Eti.id, &Eti);
	HashTableInsert(hash, &Oran.id, &Oran);

	if(0.00833333333333333333333333333333 == HashTableLoad(hash))
	{
		printf("Test HashTableLoad 2 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableLoad 2 failed!\n");
	}

	HashTableDestroy(hash);
	
	hash = HashTableCreate(OneIndexHashFunction, HashCmpFunc, 20);
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	HashTableInsert(hash, &Avi.id, &Avi);
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	HashTableInsert(hash, &Eti.id, &Eti);

	if(0.25 == HashTableLoad(hash))
	{
		printf("Test HashTableLoad 3 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableLoad 3 failed!\n");
	}

	HashTableDestroy(hash);

	hash = HashTableCreate(OneIndexHashFunction, HashCmpFunc, 1);
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	HashTableInsert(hash, &Avi.id, &Avi);
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	HashTableInsert(hash, &Eti.id, &Eti);

	if(5 == HashTableLoad(hash))
	{
		printf("Test HashTableLoad 4 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableLoad 4 failed!\n");
	}

	HashTableDestroy(hash);
}


static void TestStddev(void)
{
	hash_table_t *hash = HashTableCreate(FourIndexHashFunction, HashCmpFunc, 4);
	
	person_t Aviad = {"Aviad Caduri", "Plumber", 76, 4};
	person_t Avi = {"Avi Levi", "Cleaner", 11, 4};
	person_t Avia = {"Avia David", "Carpenter", 13, 4};
	person_t Eli = {"Eli Levi", "Musician", 89, 4};
	person_t Eti = {"Eti Levi", "Athlete", 54, 4};
	person_t Oran = {"Oran Levi", "Office manager", 73, 4};
	person_t Ofir = {"Ofir Levi", "Constructor", 71, 4};
	person_t Yarin = {"Yarin Levi", "Finance", 33, 3};
	person_t Timor = {"Timor Levi", "Finance", 18, 3};
	person_t Ella = {"Ella Levi", "Plumber", 20, 3};
	person_t Eliav = {"Eliav Levi", "Teacher", 22, 3};
	person_t Aaron = {"Aaron Cohen", "A/C tech", 5, 2};
	person_t Natan = {"Natan Cohen", "Soccer player", 67, 2};
	person_t Dor = {"Dor Cohen", "A/C tech", 55, 2};
	person_t Amit = {"Amit Cohen", "Actor", 55, 2};
	person_t Shahar = {"Shahar Cohen", "Mentor", 22, 1};
	person_t Matan = {"Matan Cohen", "Handyman", 16, 1};
	person_t Or = {"Or Cohen", "A/C tech", 27, 1};
	person_t Ori = {"Ori Cohen", "Student", 26, 1};
	person_t Oriah = {"Oriah Cohen", "Bussines", 45, 1};
	
	HashTableInsert(hash, &Aviad.id, &Aviad);
	HashTableInsert(hash, &Avi.id, &Avi);
	HashTableInsert(hash, &Avia.id, &Avia);
	HashTableInsert(hash, &Eli.id, &Eli);
	HashTableInsert(hash, &Eti.id, &Eti);
	HashTableInsert(hash, &Oran.id, &Oran);
	HashTableInsert(hash, &Ofir.id, &Ofir);
	HashTableInsert(hash, &Yarin.id, &Yarin);
	HashTableInsert(hash, &Timor.id, &Timor);
	HashTableInsert(hash, &Ella.id, &Ella);
	HashTableInsert(hash, &Eliav.id, &Eliav);
	HashTableInsert(hash, &Aaron.id, &Aaron);
	HashTableInsert(hash, &Natan.id, &Natan);
	HashTableInsert(hash, &Dor.id, &Dor);
	HashTableInsert(hash, &Amit.id, &Amit);
	HashTableInsert(hash, &Shahar.id, &Shahar);
	HashTableInsert(hash, &Matan.id, &Matan);
	HashTableInsert(hash, &Or.id, &Or);
	HashTableInsert(hash, &Ori.id, &Ori);
	HashTableInsert(hash, &Oriah.id, &Oriah);

	/* load = 5, elements in buckets [7, 5, 4, 4] */
	if(1.2247448713915890490986420373529 == HashTableStandardDeviation(hash))
	{
		printf("Test HashTableStandardDeviation 1 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableStandardDeviation 1 failed!\n");
	}
	
	HashTableRemove(hash, &Aviad.id);
	HashTableRemove(hash, &Avi.id);
	HashTableRemove(hash, &Avia.id);
	HashTableRemove(hash, &Oriah.id);
	
	/* load = 4, elements in buckets [4, 4, 4, 4] */
	if(0 == HashTableStandardDeviation(hash))
	{
		printf("Test HashTableStandardDeviation 2 passed!\n");
	}
	else
	{
		++checker;
		printf("Test HashTableStandardDeviation 2 failed!\n");
	}
	
	HashTableDestroy(hash);
}
