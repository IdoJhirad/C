#include <stdlib.h> /* size_t malloc() free() */
#include <assert.h> /* assert() */

#include "sllist.h"


struct sllist_node /*sllist_iter_t*/
{
    void *data;
     struct sllist_node *next;
};

struct sllist /*sllist_t*/
{
     struct sllist_node *head;
     struct sllist_node *tail;
};

static int IsDummy(sllist_iter_t iter);
static sllist_iter_t CreateNode(void *data , sllist_iter_t next);
static int Count(void *data, void* param);


sllist_t *SllistCreate(void)
{
	sllist_iter_t dummy = NULL;
	sllist_t *list = (sllist_t*)malloc(sizeof(struct sllist));
	if(NULL == list)
	{
		return NULL;
	}
	dummy = CreateNode(list, NULL);
	if(NULL == dummy)
	{
		free(list);
		return NULL;
	}
	
	list -> head = dummy;
	list -> tail =  dummy;

    return list;

}  



void SllistDestroy(sllist_t *sllist)  
{
	sllist_iter_t current = NULL;
	sllist_iter_t next = NULL;
	
	if (NULL == sllist) 
	{
		return;
	}

	current = sllist->head;
	while (NULL != current ) 
	{
		next = current->next; 
		free(current);
		current = next; 
	}
	
	free(sllist);
	sllist = NULL;
}





sllist_iter_t SllistNext(sllist_iter_t iter)/**/
{
	assert(iter);
	return iter->next;
}


sllist_iter_t SllistBegin(const sllist_t *sllist)/**/
{
	assert(sllist);
	return sllist -> head;
}

sllist_iter_t SllistEnd(const sllist_t *sllist)/**/
{
	assert(sllist);
	return sllist -> tail;
}


sllist_iter_t SllistInsertBefore(sllist_t *sllist, void *data, sllist_iter_t where)
{	
	sllist_iter_t new = NULL;
	assert(where);
	assert(sllist);
	new = CreateNode(where -> data,where -> next);
	if(NULL == new)
	{
		return SllistEnd(sllist);
	}
	
	if(IsDummy(where))
	{
		sllist-> tail = new;
	}
	where->data = data;
    where->next = new;
          
    return where;
}


sllist_iter_t SllistRemove(sllist_iter_t where) /*problaly wil have some issues*/
{ 
	sllist_iter_t temp = NULL;
	assert(where);
	
	temp = where -> next;
	
	where -> data = where -> next -> data;
	where -> next = where->next-> next;
	
	if(IsDummy(where))
	{
		((sllist_t *)(where->data))-> tail = where;
	}
		
	
	free(temp);

	return where;	
}




size_t SllistCount(const sllist_t *sllist)
{
	 size_t count = 0 ;
 	assert(sllist);
	SllistForEach( sllist -> head, sllist -> tail, Count , &count );
	
	return count;
}



int SllistForEach(sllist_iter_t from, sllist_iter_t to, action_func_t action, void *param)
{
	int status = 0;
	while(from != to)
	{
		status = action(from, param);
		from = from -> next;	
	}

	return status;	
}

void *SllistGetData(sllist_iter_t iterator)
{
	assert(iterator);
	return iterator -> data;
}


sllist_iter_t SllistSetData(sllist_iter_t iterator, void *new_data)
{
	assert(iterator);
	assert(new_data);	
	iterator -> data = new_data;
	 return iterator ;
}	

sllist_iter_t SllistFind(void *param, sllist_iter_t from, sllist_iter_t to, match_func_t is_match)
{
	assert(from);
	assert(to);
	assert(is_match);

	while(from != to)
	{
		if(is_match(from -> data ,param ))
		{
			return from;
		}
		from = from -> next;
		
	}
	return to;
}


int SllistIterIsEqual(sllist_iter_t iterator1, sllist_iter_t iterator2)
{
	assert(iterator1);
	assert(iterator2);
	return ( iterator1  == iterator2);
}


int SllistIsEmpty(const sllist_t *sllist)
{
	return  (SllistEnd(sllist) == SllistBegin(sllist));
}

void SllistAppend(sllist_t *dest, sllist_t *src)
{	
	assert( NULL != src);
	assert( NULL != dest);
	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;
	
	dest->tail = src->tail;
	dest->tail->data = dest;
		
	src->head->next = NULL;
	src->head->data = src;
	src->tail =src->head;

}

static int Count(void *data, void* param)
{
	(void)data;
	++(*(size_t *)param);
	return 0;

}
 
static sllist_iter_t CreateNode(void *data , sllist_iter_t next)
{
	sllist_iter_t new_node = (sllist_iter_t)malloc(sizeof(struct sllist_node));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node ->next = next;
	return new_node;
} 

static int IsDummy(sllist_iter_t iter)
{
	if(iter-> next == NULL)
	{
		return 1;
	}
	return 0;
}
