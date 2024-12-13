
/* 
   Code by: ido jhirad	
   Project: 
   Date: 
   Review by: 
   Review Date: 
   Approved by: 
   Approval Date: 
*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/

#include "sllist.h"
#include "queue.h"

struct queue 
{
	sllist_t *list;
};


 queue_t *QCreate(void)
{
	sllist_t *list  = NULL;
	queue_t *queue = (struct queue *) malloc (sizeof(struct queue));
	
	if(NULL == queue  )
	{
		return NULL;
	}
	
	list  = SllistCreate();
	if(NULL == list  )
	{
		free(queue);
		
		return NULL;
	}
	
	queue -> list =  list;
	
	return queue;
}



void QDestroy(queue_t *queue)
{
	SllistDestroy(queue ->list);
	free(queue);
}

int QEnqueue(queue_t *queue, void *data)
{
	sllist_iter_t iter =NULL;
	
	 iter = SllistInsertBefore(queue -> list, data, SllistEnd(queue -> list));
	 
	if(SllistEnd(queue -> list) == iter)
	{
		return 1;
	}
	
	return 0;
}


void QDequeue(queue_t *queue)
{
	assert(queue);
	SllistRemove(SllistBegin(queue -> list) );
}


size_t QSize(const queue_t *queue)
{
	size_t size = 0;
	assert(queue);
	size = SllistCount(queue -> list);
	
	return size;
}

void *QPeek(const queue_t *queue)
{
	void *peek = SllistGetData(SllistBegin(queue -> list));
	assert(queue);
	
	return peek;
}


int QIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return SllistIsEmpty(queue-> list);
}


void QAppend(queue_t *dest_queue, queue_t *src_queue)
{
	assert(src_queue);
	assert(dest_queue);
	SllistAppend(dest_queue-> list, src_queue-> list);

}


