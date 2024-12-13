#include <stdio.h>
#include <string.h>
#include "sortedlist.h"

char buffer[200];

void AddFailedTest(char* ptr)
{
	strcat(buffer, ptr);
}

/**/
typedef struct student
{
	char *name;
	int math_grade;
	int history_grade;
	int sport_grade;
}student_t;

/**/
int CompareStudentsByMathGrade(const void *data, const void *new_data)
{
	student_t *a = (student_t *)data;
	student_t *b = (student_t *)new_data;
	return (a->math_grade) - (b->math_grade);
}


int CompareInt(const void *data, const void *param)
{	
	return (*(int *)data - *(int *)param);
}

int TestCreateAndDestroy(sortedlist_cmp_func_t simple_test_function)
{
	sortedlist_t *list = SortedlistCreate(simple_test_function);
	if(NULL==list)
	{
		AddFailedTest("simple test for create faild\n");
		return 1;
	}
	SortedlistDestroy(list);
	return 0;
}

int TestInsertAndAllThetravers(int *data,sortedlist_cmp_func_t simple_test_function )
{	
	sortedlist_iter_t iter = {NULL};
	 int num = 5;
	sortedlist_t *list = SortedlistCreate(simple_test_function);
	if(NULL==list)
	{
		AddFailedTest("create faild inTestInsertAndAllThetravers \n");
		return 1;
	}
	iter = SortedlistGetEnd(list);
	iter = SortedlistInsert(list, data);
	iter = SortedlistInsert(list, (data+1));
	iter = SortedlistInsert(list, (data+2));
	iter = SortedlistInsert(list, (data+3));

	iter = SortedlistGetBegin(list);
	if(*(int*)SortedlistGetData(iter) != -1)
	{
		AddFailedTest("insert or getbegin faild1 \n");
		SortedlistDestroy(list);
		return 1;
	}
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);
	if(*(int*)SortedlistGetData(iter) != 20)
	{
		AddFailedTest("insert or getbegin faild2 \n");
		SortedlistDestroy(list);
		return 1;
	}
	iter = SortedlistPrev(iter);
	if(*(int*)SortedlistGetData(iter) != 15)
	{
		AddFailedTest("insert or getbegin faild 3\n");
		SortedlistDestroy(list);
		return 1;
	}
	iter = SortedlistPrev(iter);
	if(*(int*)SortedlistGetData(iter) != 1)
	{
		AddFailedTest("insert or getbegin faild4 \n");
		SortedlistDestroy(list);
		return 1;
	}	
	iter = SortedlistPrev(iter);
	if(*(int*)SortedlistGetData(iter) !=
	 *(int*)SortedlistGetData(SortedlistGetBegin(list)))
	{
		AddFailedTest("insert or getbegin faild 6\n");
		SortedlistDestroy(list);
		return 1;
	}
	iter = 	SortedlistInsert(list , &num);
	iter = SortedlistGetBegin(list);
	iter = SortedlistNext(iter);
	iter = SortedlistNext(iter);
	if(*(int*)SortedlistGetData(iter) != 5)
	{
		AddFailedTest("insert or getbegin faild \n");
		SortedlistDestroy(list);
		return 1;
	}
	SortedlistDestroy(list);
	
	return 0;
}


int TestRemoveAndSize(int *data,sortedlist_cmp_func_t simple_test_function )
{
	sortedlist_iter_t iter = {NULL};
	 int num = 5;
	sortedlist_t *list = SortedlistCreate(simple_test_function);
	if(NULL==list)
	{
		AddFailedTest("create faild inTestInsertAndAllThetravers \n");
		return 1;
	}
	if(SortedlistSize(list)!= 0)
	{
		AddFailedTest("size faild 1\n");
		return 1;
	}
	iter = SortedlistGetEnd(list);
	iter = SortedlistInsert(list, data);
	iter = SortedlistInsert(list, (data+1));
	iter = SortedlistInsert(list, (data+2));
	iter = SortedlistInsert(list, (data+3));
	iter = SortedlistInsert(list, (data+4));
	iter = SortedlistGetBegin(list);
	if(SortedlistSize(list)!= 5)
	{
		AddFailedTest("size faild2 \n");
		return 1;
	}
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);
	iter = SortedlistRemove(iter);
	if(SortedlistSize(list)!= 4)
	{
		AddFailedTest("size faild3 \n");
		return 1;
	}
	iter = SortedlistPrev(iter);
	
	if(*(int*)SortedlistGetData(iter) != 15)
	{
		AddFailedTest("insert or getbegin faild 1\n");
		SortedlistDestroy(list);
		return 1;
	}
	iter = SortedlistPrev(iter);
	iter = SortedlistRemove(iter);
	iter = 	SortedlistInsert(list , &num);
	iter = SortedlistGetBegin(list);
	iter = SortedlistNext(iter);
	iter = SortedlistNext(iter);
	iter = SortedlistNext(iter);
	if(*(int*)SortedlistGetData(iter) != 15)
	{
		AddFailedTest("insert or getbegin faild 2\n");
		SortedlistDestroy(list);
		return 1;
	}
	iter = SortedlistRemove(iter);
	if(SortedlistSize(list)!= 3)
	{
		AddFailedTest("size faild \n");
		return 1;
	}
	SortedlistDestroy(list);
	
	return 0;
}


int TestFindAndSameIter(int *data,sortedlist_cmp_func_t simple_test_function )
{	
	sortedlist_iter_t iter = {NULL};
	sortedlist_iter_t node = {NULL};
	 int find = 20;
	sortedlist_t *list = SortedlistCreate(simple_test_function);
	if(NULL==list)
	{
		AddFailedTest("create faild inTestInsertAndAllThetravers \n");
		return 1;
	}
	iter = SortedlistGetEnd(list);
	iter = SortedlistInsert(list, data);
	iter = SortedlistInsert(list, (data+1));
	iter = SortedlistInsert(list, (data+2));
	iter = SortedlistInsert(list, (data+3));

	iter = SortedlistGetBegin(list);
	
	node = SortedlistFind(list, SortedlistGetBegin(list),SortedlistGetEnd(list),&find);
	
	if(*(int*)SortedlistGetData(node) != 20)
	{
		AddFailedTest("SortedlistFind \n");
		SortedlistDestroy(list);
		return 1;
	}
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);

	iter = SortedlistPrev(iter);
	if(*(int*)SortedlistGetData(iter) != 15)
	{
		AddFailedTest("insert or getbegin faild 3\n");
		SortedlistDestroy(list);
		return 1;
	}
	find = 55;
	node = SortedlistFind(list, SortedlistGetBegin(list),SortedlistGetEnd(list),&find);
	if(!SortedlistIsSameIter(node, SortedlistGetEnd(list)))
	{
		AddFailedTest("Sortedlist Find or same iter faild \n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	
	return 0;
}


int TestMerge(int *data,sortedlist_cmp_func_t simple_test_function, int* data2 )
{	
	sortedlist_iter_t iter = {NULL};
	sortedlist_iter_t iter2 = {NULL};
	sortedlist_t *list = SortedlistCreate(simple_test_function);
	sortedlist_t *list2 = SortedlistCreate(simple_test_function);
	iter = SortedlistGetBegin(list);
	iter = SortedlistInsert(list, data);
	iter = SortedlistInsert(list, (data+1));
	iter = SortedlistInsert(list, (data+2));
	iter = SortedlistInsert(list, (data+3));
	iter = SortedlistInsert(list, (data+4));

	iter2 = SortedlistGetBegin(list2);
	iter2 = SortedlistInsert(list2, data2);
	iter2=  SortedlistInsert(list2, (data2+1));
	iter2 = SortedlistInsert(list2, (data2+2));
	iter2 = SortedlistInsert(list2, (data2+3));
	iter2 = SortedlistInsert(list2, (data2+4));
 
	SortedlistMerge(list , list2);
	if(!SortedlistIsEmpty(list2))
	{
		AddFailedTest("SortedlistMerge or is empty faild \n");
		SortedlistDestroy(list);
		SortedlistDestroy(list2);
		return 1;
	}
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);
	if(*(int*)SortedlistGetData(iter) != 67)
	{
		AddFailedTest("merge faild\n");
		SortedlistDestroy(list);
		return 1;
	}

	SortedlistDestroy(list);
	SortedlistDestroy(list2);
	return 0;
}

int IsAllGradesAbove85( const void *data,const  void *param)
{
	student_t *student = (student_t *)data;
	int grade = *(int *)param;
	if(student->math_grade > grade && student->history_grade > grade && student->sport_grade > grade)
	{
		return 1;
	}
	
	return 0;
}

int TestFindIf(sortedlist_cmp_func_t CompareStudentsByMathGrade )
{	
	int grade_to_check = 85;
	sortedlist_t *slist = SortedlistCreate(CompareStudentsByMathGrade);

	student_t avi = {"avi cohen", 90, 92, 89};
	student_t dan = {"dan levi", 87, 68, 100};
	student_t david = {"david levi", 97, 77, 86};
	student_t roee = {"roee perez", 60, 90, 100};
	student_t amit = {"amit elad", 91, 56, 95};
	student_t yan = {"yan meiri", 98, 87, 92};
	
	student_t *temp = NULL;
	sortedlist_iter_t iter = {NULL};
	
	iter = SortedlistInsert(slist, &avi);
	iter = SortedlistInsert(slist, &dan);
	iter = SortedlistInsert(slist, &david);
	iter = SortedlistInsert(slist, &roee);
	iter = SortedlistInsert(slist, &amit);
	iter = SortedlistInsert(slist, &yan);
	
	iter = SortedlistFindIf(SortedlistGetBegin(slist), SortedlistGetEnd(slist), IsAllGradesAbove85, &grade_to_check);
	temp = (student_t *)SortedlistGetData(iter);
	if(0 !=(strcmp("avi cohen", temp->name)))
	{
		AddFailedTest("SortedlistFindIf failed\n");
		SortedlistDestroy(slist);
		return 1;;
	}

	SortedlistDestroy(slist);
	return 0;
}	

int PrintList(const void *data,const  void *param)
{
	student_t *student = (student_t *)data;
	++*(size_t *)param;
	printf("%s %d %d %d\n", student->name, student->math_grade, student->history_grade, student->sport_grade);
	return 0;
}


int TestForEach(sortedlist_cmp_func_t CompareStudentsByMathGrade )
{	

	sortedlist_t *slist = SortedlistCreate(CompareStudentsByMathGrade);
	size_t count = 0;
	student_t avi = {"avi cohen", 90, 92, 89};
	student_t dan = {"dan levi", 87, 68, 100};
	student_t david = {"david levi", 97, 77, 86};
	student_t roee = {"roee perez", 60, 90, 100};
	student_t amit = {"amit elad", 91, 56, 95};
	student_t yan = {"yan meiri", 98, 87, 92};
	

	sortedlist_iter_t iter = {NULL};
	
	iter = SortedlistInsert(slist, &avi);
	iter = SortedlistInsert(slist, &dan);
	iter = SortedlistInsert(slist, &david);
	iter = SortedlistInsert(slist, &roee);
	iter = SortedlistInsert(slist, &amit);
	iter = SortedlistInsert(slist, &yan);
	
	SortedlistForEach(SortedlistGetBegin(slist), SortedlistGetEnd(slist), PrintList, &count);
	SortedlistDestroy(slist);
	return 0;
}	


int main(void)
{
	int test_indicator = 0;
	sortedlist_cmp_func_t simple_test_function = CompareInt;
	int data[5]= {15, 20, 1, -1, 7};
	int data2[5]={ -4,32,67,43,-53};
	
	/*simple teat on ints*/
	test_indicator += TestCreateAndDestroy(simple_test_function);
	printf("simple test for create\n");
	
	test_indicator += TestInsertAndAllThetravers( data,simple_test_function );
	printf("test for insert and travers\n");
	
	test_indicator += TestRemoveAndSize( data,simple_test_function );
	printf("test for remove and size\n");
	
	test_indicator += TestFindAndSameIter( data,simple_test_function );
	printf("test for find and same iter\n");
	
	test_indicator += TestMerge( data,simple_test_function, data2 );
	printf("merge\n");
	
	test_indicator += TestFindIf( CompareStudentsByMathGrade );
	printf("find if\n");
	
	test_indicator += TestForEach( CompareStudentsByMathGrade );
	printf("for each\n");	
	if (test_indicator)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, test_indicator, 10, buffer);
		return test_indicator;
	}

	printf("all test passed\n");

	return 0;
}


