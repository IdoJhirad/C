
/* 
   Code by: ido jhirad	
   Project: scheduler
   Date: 01/05/24
   Review by: sahar
   Review Date: 03/06/24
   Approved by: sahar
   Approval Date: 03/06/24
*/
#include <sys/types.h> /* size_t, time_t*/
#include <assert.h> /* assert */
#include <time.h> /* time */
#include <stdlib.h> /*malloc*/
#include <unistd.h> /* sleep*/

#include "task.h"
#include "pq.h"
#include "uid.h"
#include "scheduler.h"

static int IsTheSameUid(const void *task, const void *param) ;
static int CompareItemPriority(const void *data, const void *param);

struct scheduler
{
    pq_t *task_queue;
    int run;
};

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = (scheduler_t *) malloc(sizeof(struct scheduler));
	if(NULL == scheduler)
	{
		return NULL;   
	}
	scheduler->task_queue = PQCreate(CompareItemPriority);
	if(NULL == scheduler->task_queue)
	{
		free(scheduler);
		
		return NULL;
	}	
	scheduler->run = 0;
	return scheduler;
}

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler);
	
	SchedulerClear(scheduler);
	PQDestroy(scheduler->task_queue);
	free(scheduler);
}

ilrd_uid_t SchedulerAdd(scheduler_t *scheduler,
                    time_t exec_time, 
                    time_t interval_in_seconds, 
                    void (*action)(void *params), 
                    void *params)
{
	task_t *new_task = NULL;
	
	assert(scheduler);
	assert(exec_time);
	
	new_task = TaskCreate(exec_time, interval_in_seconds, action, params);
	if(NULL == new_task )
	{
		return BadUID;
	}

	if(PQEnqueue(scheduler->task_queue, new_task))
	{
		TaskDestroy(new_task);
		return BadUID;
	}
	return GetUid(new_task);
}

int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{
	task_t *removed_task = NULL;
	
	assert(scheduler);
	assert(scheduler->task_queue);
	
	removed_task = (task_t*)PQErase(scheduler->task_queue , IsTheSameUid , &uid);
	if(NULL == removed_task)	
	{
		return SCHEDULER_UID_NOT_FOUND;
	}
	TaskDestroy(removed_task);
	
	return SUCCESS;
}

int SchedulerRun(scheduler_t *scheduler)
{
	task_t * curr = NULL ;
	time_t exec_time = 0;
	time_t interval = 0;
    time_t time_to_sleep = 0;
    scheduler->run = 1;
    
    assert(scheduler);
	assert(scheduler->task_queue);
    	
	while(scheduler->run  && !SchedulerIsEmpty(scheduler))
	{
		curr = PQPeek(scheduler->task_queue);
		exec_time = GetExecTime(curr);
		interval = GetInterval(curr);
		PQDequeue(scheduler->task_queue);
		
		if(exec_time <  time(NULL))
		{
			TaskDestroy(curr);
		}
		else
		{
			time_to_sleep = exec_time - time(NULL);
			
			while(time_to_sleep)
			{
				time_to_sleep = sleep(time_to_sleep);
			}
			
			TaskRun(curr);
			
			if(interval)
			{
				UpdateExecTime(curr , exec_time + interval );
				PQEnqueue(scheduler->task_queue, curr);
			}
			else
			{
				TaskDestroy(curr);
			}

		}
	}

	return (!SchedulerIsEmpty(scheduler)) ? SCHEDULER_STOP : SUCCESS;
}

void SchedulerStop(scheduler_t *scheduler)
{
    assert(scheduler);
	    
	scheduler->run = 0;
}

size_t SchedulerSize(scheduler_t *scheduler)
{
    assert(scheduler);
	    
	return PQSize(scheduler->task_queue);
}

int SchedulerIsEmpty(scheduler_t *scheduler)
{
    assert(scheduler);
	    
	return PQIsEmpty(scheduler->task_queue);
}

void SchedulerClear(scheduler_t *scheduler)
{
	task_t* task = NULL;
	
    assert(scheduler);
    
	while(!SchedulerIsEmpty(scheduler))
	{
		task = (task_t *)PQDequeue(scheduler->task_queue);
		TaskDestroy(task);	
	}
}	

static int IsTheSameUid(const void *task, const void *uid)
{
	return IsSameUID(GetUid((const task_t *)task), *(const ilrd_uid_t *)uid);
}
static int CompareItemPriority(const void *data, const void *param)
{
	return GetExecTime((task_t *)data) - GetExecTime((task_t *)param);
}
