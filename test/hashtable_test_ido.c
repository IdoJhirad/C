#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"

#define TESTNUM 4

static char failed_tests_print[200] = {'\0'};

void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}

int TestCreatAndDystroy();
int TestInsertAndCount();
int TestFind();
int TestForEach();
int TestRemove();
int TestLoad();

typedef struct student
{
	char *key;
	int math_grade;
	int sport_grade;
}student_t;

size_t HashFunc( const void *key)
{
	size_t i = 0;
	char* key_char = (char *)key;
	size_t lenght = strlen(key_char);
	
	size_t val_for_key = 0;
	
	while(i < lenght)
	{
		 val_for_key += key_char[i];
		 ++i;
	}
	
	return val_for_key % 10	;
		
}

int PrintData( void *data, void *params)
{
	student_t *student = (student_t *)data;
	(void)params;
	printf("%s \n", student->key);
	
	return 0;
}

int PrintString( void *data, void *params)
{
	char * string = (char *)data;
	(void)params;
	printf("%s \n", string);
	
	return 0;
}
int FreeData( void *data, void *params)
{

	(void)params;
	free(data);
	
	return 0;
}

int HashComper(const void *key1, const void *key2)
{
	student_t key_num1 = *(student_t* )key1;
	char* key_num2 = (char* )key2;
	
	assert(key1);
	assert(key2);
	
	return (strcmp(key_num1.key ,key_num2) == 0);
}
 int HashComperString(const void *key1, const void *key2)
{
	char* key_num1 = (char* )key1;
	char *key_num2 = (char* )key2;
	
	assert(key1);
	assert(key2);
	
	return (strcmp(key_num1 ,key_num2) == 0);
}
int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestCreatAndDystroy();
	printf("Tested Creat And Destroy\n");
	
	failed_tests_num += TestInsertAndCount();
	printf("Tested TestInsertAndCount\n");
	
	failed_tests_num += TestFind();
	printf("Tested TestFind\n");
	
	failed_tests_num += TestForEach();
	printf("Tested TestForEach\n");
	
	failed_tests_num += TestRemove();
	printf("Tested TestRemove\n");
	
	/*failed_tests_num += TestLoad();
	printf("Tested TestLoad\n");*/
	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}

int TestCreatAndDystroy()
{
	hash_table_t *hashtable = HashTableCreate(HashFunc, HashComper, 10);
	if(!hashtable)
	{
		AddFailedTest("create faild\n");
		return 1;
	}
	HashTableDestroy(hashtable);
	return 0;
}

int TestInsertAndCount()
{
	size_t i = 0;
	int insert_status = 0;
	student_t array[] = 
	{
		{"ido"  , 100 ,100},
		{"yaron" , 58 , 75},
		{"roei"  , 77 , 95},
		{"shlomi", 68 , 85},
		{"israel", 89 , 96},
		{"levi"  , 65 , 94}
	
	};	
	
	hash_table_t *hashtable = HashTableCreate(HashFunc, HashComper, 10);
	if(!hashtable)
	{
		AddFailedTest("create faild\n");
		return 1;
	}
	
	
	if( 0 != HashTableSize(hashtable))
	{
		AddFailedTest("size 1 faild\n");
		HashTableDestroy(hashtable);
		
		return 1;
	}
	if( 1!= HashTableIsEmpty(hashtable))
	{
		AddFailedTest("Is Empty 1 faild\n");
		HashTableDestroy(hashtable);
		
		return 1;
	}
	for(; i < 6 ; ++i)
	{
		insert_status = HashTableInsert(hashtable , array[i].key , &array[i]);
		if(0 != (size_t)insert_status)
		{
			AddFailedTest("insert 1 faild\n");
			printf("faild in %ld iteration\n",i);	
			HashTableDestroy(hashtable);
			
			return 1;
		}
		if( i+1 != HashTableSize(hashtable))
		{
			AddFailedTest("size 1 faild\n");
			printf("faild in %ld iteration\n",i);
			HashTableDestroy(hashtable);
			
			return 1;
		}
		if( 0!= HashTableIsEmpty(hashtable))
		{
			AddFailedTest("Is Empty 1 faild\n");
			HashTableDestroy(hashtable);
			
			return 1;
		}
		
	}
		
	HashTableDestroy(hashtable);
	return 0;
}

int TestFind()
{
	student_t *data = NULL;
	size_t i = 0;
	int insert_status = 0;
	student_t array[] = 
	{
		{"ido"  , 100 ,100},
		{"yaron" , 58 , 75},
		{"roei"  , 77 , 95},
		{"shlomi", 68 , 85},
		{"israel", 89 , 96},
		{"levi"  , 65 , 94}
	
	};	
	
	hash_table_t *hashtable = HashTableCreate(HashFunc, HashComper, 10);
	if(!hashtable)
	{
		AddFailedTest("create faild\n");
		return 1;
	}
	
	for(; i < 6 ; ++i)
	{
		insert_status = HashTableInsert(hashtable , array[i].key , &array[i]);
		if(0 != (size_t)insert_status)
		{
			AddFailedTest("insert 1 faild\n");
			printf("faild in %ld iteration\n",i);	
			HashTableDestroy(hashtable);
			
			return 1;
		}
		
	}
	data = (student_t *)HashTableFind(hashtable, "ido");
	if( data->key != array[0].key )
	{
		AddFailedTest("find test 1 faild\n");
		HashTableDestroy(hashtable);
			
		return 1;
	}
	data = (student_t *)HashTableFind(hashtable, "yaron");
	if( data->key != array[1].key )
	{
		AddFailedTest("find test 2 faild\n");
		HashTableDestroy(hashtable);
			
		return 1;
	}
	data = (student_t *)HashTableFind(hashtable, "roei");
	if( data->key != array[2].key )
	{
		AddFailedTest("find test 3 faild\n");
		HashTableDestroy(hashtable);
			
		return 1;
	}
	data = (student_t *)HashTableFind(hashtable, "lirom");
	if( data != NULL)
	{
		AddFailedTest("find test 4 faild\n");
		HashTableDestroy(hashtable);
			
		return 1;
	}
		
	HashTableDestroy(hashtable);
	return 0;
}

int TestForEach()
{
	size_t i = 0;
	int insert_status = 0;
	student_t array[] = 
	{
		{"ido"  , 100 ,100},
		{"yaron" , 58 , 75},
		{"roei"  , 77 , 95},
		{"shlomi", 68 , 85},
		{"israel", 89 , 96},
		{"levi"  , 65 , 94}
	
	};	
	
	hash_table_t *hashtable = HashTableCreate(HashFunc, HashComper, 10);
	if(!hashtable)
	{
		AddFailedTest("create faild\n");
		return 1;
	}
	
	for(; i < 6 ; ++i)
	{
		insert_status = HashTableInsert(hashtable , array[i].key , &array[i]);
		if(0 != (size_t)insert_status)
		{
			AddFailedTest("insert 1 faild\n");
			printf("faild in %ld iteration\n",i);	
			HashTableDestroy(hashtable);
			
			return 1;
		}
		
	}
	HashTableForEach(hashtable ,PrintData , &i);
	
		
	HashTableDestroy(hashtable);
	return 0;
}

int TestRemove()
{
	size_t i = 0;
	int insert_status = 0;
	student_t array[] = 
	{
		{"ido"  , 100 ,100},
		{"yaron" , 58 , 75},
		{"roei"  , 77 , 95},
		{"shlomi", 68 , 85},
		{"israel", 89 , 96},
		{"levi"  , 65 , 94}
	
	};	
	
	hash_table_t *hashtable = HashTableCreate(HashFunc, HashComper, 10);
	if(!hashtable)
	{
		AddFailedTest("create faild\n");
		return 1;
	}
	for(; i < 6 ; ++i)
	{
		insert_status = HashTableInsert(hashtable , &array[i].key , &array[i]);
		if(0 != (size_t)insert_status)
		{
			AddFailedTest("insert 1 faild\n");
			printf("faild in %ld iteration\n",i);	
			HashTableDestroy(hashtable);
			
			return 1;
		}
		
	}
	/*for(i = 0 ; i < 6 ; ++i)
	{
		HashTableRemove(hashtable , array[i].key);
	}*/
	
	
	HashTableRemove(hashtable , "ido");
		printf("%ld\n" , HashTableSize(hashtable));
	HashTableRemove(hashtable , "yaron");
		printf("%ld\n" , HashTableSize(hashtable));
	HashTableRemove(hashtable , "roei");
		printf("%ld\n" , HashTableSize(hashtable));
	HashTableRemove(hashtable , "shlomi");
		printf("%ld\n" , HashTableSize(hashtable));
	HashTableRemove(hashtable , "israel");
		printf("%ld\n" , HashTableSize(hashtable));
	HashTableRemove(hashtable , "levi");
	printf("%ld\n" , HashTableSize(hashtable));
	if(!HashTableIsEmpty(hashtable))
	{
			AddFailedTest("remove 1 faild\n");

			HashTableDestroy(hashtable);
			
			return 1;
	}
	if( 0 != HashTableSize(hashtable))
	{
		AddFailedTest("size 1 faild\n");
		HashTableDestroy(hashtable);
		
		return 1;
	}
	HashTableDestroy(hashtable);
	return 0;
}


int TestLoad()
{
	size_t i = 0;
	int insert_status = 0;
	char str[100]; 
	char *spell = NULL;
	char *data =NULL;
	size_t len = 0;
   
	hash_table_t *hashtable = HashTableCreate(HashFunc, HashComperString, 10);
	if(!hashtable)
	{
		AddFailedTest("create faild\n");
		return 1;
	}
	HashTableLoad(hashtable);
	if(HashTableIsEmpty(hashtable))
	{
			AddFailedTest(" hash load faild\n");

			HashTableDestroy(hashtable);
			
			return 1;
	}
	
	printf("%ld \n", HashTableSize(hashtable));
	/*HashTableForEach(hashtable , PrintString , &i);*/

    printf("Enter a string: ");
    scanf("%99s", str);

    printf("You entered: %s\n", str);
    

    
    
    data = (char *)HashTableFind(hashtable, str);
    if (data != NULL) 
    {
 	    printf("found : \n %s\n", data);
        
    }
	 else
    {
    	printf("not found : \n");
    }
	
    printf("Enter a string: ");
    scanf("%99s", str);

    printf("You entered: %s\n", str);
    

    
    
    data = (char *)HashTableFind(hashtable, str);
    if (data != NULL) 
    {
 	   printf("found : \n %s\n", data);
 	   
        
    }
    else
    {
    	printf("not found : \n");
    }
	
	HashTableForEach(hashtable , FreeData , &i);
	HashTableDestroy(hashtable);
	
	return 0;
}	


/*load dicomery*/
/*double HashTableLoad(const hash_table_t *table)
{
	char *word = NULL;
	FILE *file = fopen("/etc/dictionaries-common/words", "r");
	
	if(!file)
	{
		return 1;
	}
	 word = (char *)calloc(25 , sizeof(char));
			 
	while(fscanf(file, "%s", word) != EOF )
	{
		 HashTableInsert((hash_table_t*)table, word, word);
		 word = (char *)calloc(25 , sizeof(char));
	
	}
	free(word);
	fclose(file);
	
	return 0;

}*/
