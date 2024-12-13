#include <time.h>/* time_t */
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include "task.h"
#include "uid.h"

struct task
{
    ilrd_uid_t uid;
    time_t exe_time;
    time_t interval_in_seconds;
    void (*action)(void *params);
    void *params;
};


task_t *TaskCreate(time_t exe_time, time_t interval_in_seconds, void (*action)(void *params), void *params)											
{
	task_t *new_task = {NULL};
	
	assert(action);
	
	new_task =(task_t*) malloc(sizeof(struct task));
	if(NULL == new_task)
	{
		return NULL;
	}
	
	new_task -> exe_time = exe_time; 
	new_task -> action = action;
	new_task -> params = params;
	new_task -> interval_in_seconds = interval_in_seconds;
	new_task -> uid = UIDCreate();
	if (IsSameUID(BadUID,new_task -> uid))
	{
		free(new_task);
		return NULL;
	}
	
	return new_task;
}


void TaskDestroy(task_t *task)
{
	assert(task);
	
	free(task);
}


int TaskRun(task_t *task)
{
	assert(task);
	assert(task->action);

	 task->action(task->params);
	return 0;
}

ilrd_uid_t GetUid(const task_t *task)
{
	assert(task);
	
	return task -> uid;
}


time_t GetExecTime(task_t *task)
{
	assert(task);
	
	return task->exe_time;
}

void UpdateExecTime(task_t *task, time_t new_exe_time)
{
	assert(task);
	
	task->exe_time = new_exe_time;
}

time_t GetInterval(task_t *task)
{
	return task ->interval_in_seconds;
}

