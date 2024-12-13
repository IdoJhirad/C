
/* 
   Code by: ido jhirad	
   Project: 
   Date: 
   Review by: 
   Review Date: 
   Approved by: 
   Approval Date: 
*/
#include <stdlib.h> /* size_t malloc() free() */
#include <assert.h> /* assert() */

#include "dllist.h"

static dllist_iter_t CreatNode(void *data, dllist_iter_t next, dllist_iter_t prev);

static int Count( void *data,  void* param);

struct dllist_node 
{
    void *data;
    struct dllist_node *next;
    struct dllist_node *prev;
};

struct dllist 
{
    struct dllist_node *head;
    struct dllist_node *tail;
};



dllist_t *DllistCreate(void)
{
	dllist_t *dllist = ( dllist_t *)malloc(sizeof(struct dllist_node ));
	dllist_iter_t head_dummy = NULL;
	dllist_iter_t tail_dummy = NULL;
	
	if(NULL == dllist)
	{
		return NULL;
	}	
	head_dummy = CreatNode(NULL, NULL, NULL);
	if(NULL == head_dummy)
	{
		free(dllist);
		return NULL;
	}
	
	tail_dummy = CreatNode(NULL, NULL, head_dummy);
	if(NULL == tail_dummy)
	{
		free(dllist);
		free(head_dummy);
		return NULL;
	}
	
	head_dummy->next = tail_dummy;
	dllist -> head = head_dummy ;
	dllist -> tail = tail_dummy;
	
	return dllist;

}



void DllistDestroy(dllist_t *list)
{ 
	dllist_iter_t current = NULL;
	dllist_iter_t next = NULL;

	assert(list);

	current = list->head;
	while (NULL != current ) 
	{
		next = current->next; 
		free(current);
		current = next; 
	}

	free(current);
	free(list);

	list = NULL;
}


dllist_iter_t DllistNext(dllist_iter_t iter)
{
	assert(iter);	
	
	return  iter->next;
}

dllist_iter_t DllistPrev(dllist_iter_t iter)
{
	assert(iter);
	
	return iter->prev;
}


dllist_iter_t DllistGetBegin(const dllist_t *list)
{
	assert(list);
	
	return list->head ->next;
	
}

dllist_iter_t DllistGetEnd(const dllist_t *list)
{
	assert(list);
	
	return list -> tail;
}


dllist_iter_t DllistInsertBefore(dllist_t *list, void *data, dllist_iter_t where)
{
	dllist_iter_t new_node = NULL;
	dllist_iter_t prev_node = where -> prev;
	dllist_iter_t next_node = where ;
	
	assert(where);
	assert(list);
	assert(data);
	
	
	new_node = CreatNode(data, next_node, prev_node);
	if(NULL == new_node )
	{
		return list->tail;
	}
	
	
	prev_node -> next = new_node;
	where -> prev = new_node;
	
	return new_node;
}



dllist_iter_t DllistRemove(dllist_iter_t where)
{
		dllist_iter_t prev_node = NULL;
		dllist_iter_t next_node = NULL; 
		assert(where);
		
		prev_node = where -> prev; 
		next_node = where -> next; 
		
		prev_node -> next = next_node;
		next_node -> prev = prev_node;
		
		free(where);
		
		return next_node;
}

size_t DllistSize(const dllist_t *list)
{
	size_t count = 0;
	
 	assert(list);
 	
	DllistForEach(DllistGetBegin(list), DllistGetEnd(list), Count , &count);
	
	return count;
}

void *DllistGetData(dllist_iter_t iter)
{	
	assert(iter);	
	
	return iter-> data;
}


dllist_iter_t DllistFind(void *param, dllist_iter_t from, dllist_iter_t to, match_func_t is_match)
{
	assert(is_match);
	assert(to);
	assert(from);
	
	while(from != to)
	{
		if(is_match(from -> data ,param ))
		{
			return from;
		}
		from = DllistNext(from);
		
	}
	
	return to;
}

int DllistIsSameIter(dllist_iter_t iter1, dllist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return (iter1 == iter2);
}

    
int DllistIsEmpty(const dllist_t *list)
{
	assert(list);
	
	return DllistGetBegin(list) == DllistGetEnd(list);
}

void DllistSetData(dllist_iter_t iter, void* data)
{
	assert(iter);

	iter->data = data;
}


int DllistForEach(dllist_iter_t from, dllist_iter_t to, action_func_t action,
				 void *param)
{
	int status = 0;
	
	assert(from);
	assert(to);

	
	while(from != to)
	{
		status = action(from-> data, param);
		from = DllistNext(from);	
	}

	return status;	
}


dllist_iter_t DllistSplice(dllist_iter_t where, dllist_iter_t from, dllist_iter_t to)
{
	
	dllist_iter_t before_from = NULL;
	
	assert(where);
	assert(from);
	assert(to);
	
	before_from = from->prev ; 
	where->prev->next = from;
	from->prev->next = to;
	
	to->prev->next = where;
	from->prev = where->prev;
	
	where->prev = to->prev;
	to->prev = before_from;
	
	return where -> prev;
}

dllist_iter_t DllistPushFront(dllist_t *list, void *data)
{
	assert(data);
	assert(list);
	
	return DllistInsertBefore(list, data, list -> head->next);
}


dllist_iter_t DllistPushBack(dllist_t *list, void *data)
{
	assert(data);
	assert(list);
	
	return DllistInsertBefore(list, data, DllistGetEnd(list));
}


void *DllistPopFront(dllist_t *list)
{
	void *head_data  = NULL;
	assert(list);
	head_data = list ->head->next->data;
	
	assert(list);
	
	DllistRemove( DllistGetBegin(list));
	
	return head_data;
}

void *DllistPopBack(dllist_t *list)
{
	void *node_data  = NULL;
	dllist_iter_t last_valid =NULL;
	assert(list);
	
	last_valid =list->tail->prev;
	node_data = last_valid->data;
	
	DllistRemove( last_valid );
	
	return node_data;
}

int DllistMultiFind(dllist_iter_t from, dllist_iter_t to, match_func_t is_match, void *param, dllist_t *output)
{
	int status = 0;
	dllist_iter_t ptr = NULL;
	
	assert(from);
	assert(to);
	assert(is_match);


	
	while(from != to)
	{
		if(is_match(from -> data ,param ))
		{
			ptr = DllistInsertBefore(output, from -> data, output -> head->next);
			++status;
			if(NULL == ptr)
			{
				return -1;
			}
		}
		from = DllistNext(from); 
	}
	return status;
}


static dllist_iter_t CreatNode(void *data, dllist_iter_t next, dllist_iter_t prev)
{
 	dllist_iter_t new_node = (dllist_iter_t)malloc(sizeof(struct dllist_node ));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node -> data = data;
	new_node -> next = next;
	new_node -> prev = prev;
	
	return new_node;
}



static int Count( void *data,  void* param)
{
	(void)data;
	++(*(size_t *)param);
	
	return 0;
}


