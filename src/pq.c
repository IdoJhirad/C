
/* 
   Code by: ido jhirad	
   Project:  pq
   Date: 29.5.2024
   Review by: oded
   Review Date: 30.05.2024
   Approved by: oded
   Approval Date: 30.5.2024
*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/
#include <assert.h>/*assert*/
#include "sortedlist.h"
#include "pq.h"

struct pq
{
 	sortedlist_t *list;
};

pq_t *PQCreate(pq_compare_func_t cmp_func)
{
	pq_t *new = NULL;
	
	assert(cmp_func);
	new = (pq_t*)malloc(sizeof(struct pq));
	if(NULL == new)
	{
		return NULL;
	}
	
	new -> list = SortedlistCreate(cmp_func);
	if(NULL == new -> list)
	{
		free(new);
		
		return NULL;
	}
	
	return new;
}

void PQDestroy(pq_t *queue)
{
	assert(queue);
	assert(queue->list);
	
	SortedlistDestroy(queue->list);	
	free(queue);
}	
	
int PQEnqueue(pq_t *queue, void *data)
{
	assert(queue);
	assert(queue->list);

	SortedlistInsert(queue->list ,data );
	
	return 0;
}

void *PQDequeue(pq_t *queue)
{
	sortedlist_iter_t first = {NULL};	
	void *data =NULL; 
	
	assert(queue);
	assert(queue->list);
	
	 first = SortedlistGetBegin(queue->list);
	 
	 if(1 == PQIsEmpty(queue))
	 {

	 	return NULL;
	 }
	 data = SortedlistGetData(first);
	 first = SortedlistRemove(first);
	 
	 return data;
	
}

void *PQPeek(const pq_t *queue)
{
	sortedlist_iter_t begin = {NULL}; 
	
	assert(queue);
	assert(queue->list);

	begin = SortedlistGetBegin(queue->list);
	if(1 == PQIsEmpty(queue))
	{
	 	return NULL;
	}
	
	return (SortedlistGetData(begin));
}

int PQIsEmpty(const pq_t *queue)
{
	assert(queue);
	assert(queue->list);
	
	return SortedlistIsEmpty(queue->list);
}

size_t PQSize(const pq_t *queue)
{
	assert(queue);
	assert(queue->list);
	
	return SortedlistSize(queue->list);
}

void PQClear(pq_t *queue)
{
	assert(queue);
	assert(queue->list);
	
	while (1 != PQIsEmpty(queue))
	{
		PQDequeue(queue);
	}
}

void *PQErase(pq_t *queue, pq_match_func_t is_match , void *param)
{
	sortedlist_iter_t node = {NULL};	
	void *data = NULL;
	assert(queue);
	assert(queue->list);
	assert(is_match);
	
	node = SortedlistFindIf(SortedlistGetBegin(queue->list),
							SortedlistGetEnd(queue->list),is_match, param);
	
	if (SortedlistIsSameIter(node,SortedlistGetEnd(queue->list))) 
	{
        return NULL;
    }
    data = SortedlistGetData(node);
	SortedlistRemove(node);
	
	return data;
}



