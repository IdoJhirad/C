#include <sys/types.h>/* pid_t time_t size_t*/
#include <time.h>/*time*/
#include <unistd.h>/*getpid*/
#include <pthread.h> /* pthread_mutex_t */

#include "uid.h"

const ilrd_uid_t BadUID = {0 , 0 , 0};
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static size_t serial_count = 0;

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t uid;

	pid_t pid = getpid();
	
	if(1==pid)
	{
		return BadUID;
	}
	
    uid.timestamp = time(NULL);
    if(-1 == uid.timestamp)
	{
		return BadUID;
	}
	uid.pid = pid;
	/*make uid thread safe*/
    pthread_mutex_lock(&mutex);
	++serial_count;
	pthread_mutex_unlock(&mutex);
	
	uid.counter = serial_count;
	
	return uid;
}

int IsSameUID(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	return (uid1.counter == uid2.counter)&&uid1.timestamp == uid2.timestamp;
}



