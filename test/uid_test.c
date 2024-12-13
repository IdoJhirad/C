
#include <stdio.h>

#include "uid.h"


int main(void)
{
	ilrd_uid_t new; 

	ilrd_uid_t new2 ;

	ilrd_uid_t new3 ;
	
	new = UIDCreate();
	printf("uid1\n");
	printf("the pid is: %d\n", new.pid);
	printf("the time is: %ld\n", new.timestamp);
	printf("the counter is: %ld\n", new.counter);

	sleep(2);
	new2 = UIDCreate();
	printf("uid2\n");
	printf("the pid is: %d\n", new2.pid);
	printf("the time is: %ld\n", new2.timestamp);
	printf("the counter is: %ld\n", new2.counter);

	sleep(2);
	new3 = UIDCreate();
	printf("uid3\n");
	printf("the pid is: %d\n", new3.pid);
	printf("the time is: %ld\n", new3.timestamp);
	printf("the counter is: %ld\n", new3.counter);
	if(IsSameUID(new,new2))
	{
		printf("is same uid faild");
	}
	else
	{
		printf("is same uid sucseed\n");	
	}
	

	return 0;
}
