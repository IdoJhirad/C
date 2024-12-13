/* -------------------------------------------------------------------------- *
 * 									Headers
 * -------------------------------------------------------------------------- */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h> /* time() */

#include "scheduler.h"
#include "uid.h"

/* -------------------------------------------------------------------------- *
 * 									Prototypes
 * -------------------------------------------------------------------------- */
static void RickTest(void);

void EnAll(void);
void DisAll(void);
int CloseTest(void *data);
void RollFunction(void *data);
void NewLine(void *data);
void LyricFunction(void *second);
void CloseTab(void *data);
void SchedulerStopWrapper(void *params);

/* -------------------------------------------------------------------------- *
 * 									Definitions
 * -------------------------------------------------------------------------- */
enum test_type
{
	HEAP = 0,
	SORTED_LIST = 1
};

/*static char str[1000] = {0};
static char *runner = str;*/

/* -------------------------------------------------------------------------- *
 * 									Main
 * -------------------------------------------------------------------------- */
int main(void)
{
	RickTest();

	return 0;
}

/* -------------------------------------------------------------------------- *
 * 									Functions
 * -------------------------------------------------------------------------- */
static void RickTest(void)
{
	/*--------------------------------------------------------*
	 * 				Variable Declarations
	 *-------------------------------------------------------*/
	scheduler_t *sched = NULL;
	int second = 17;

	/*--------------------------------------------------------*
	 * 				Variable Initialization
	 *-------------------------------------------------------*/
	printf("RickTest()\nPlease enjoy! (I'm sorry) :)\n\n");

	/*--------------------------------------------------------*
	 * 				SchedulerCreate
	 *-------------------------------------------------------*/
	sched = SchedulerCreate();

	/*DisAll();*/

	/*--------------------------------------------------------*
	 * 				SchedulerAdd
	 *-------------------------------------------------------*/
	SchedulerAdd(sched, time(NULL) + 3, 0, RollFunction, NULL);
	SchedulerAdd(sched, time(NULL) + 17, 1, LyricFunction, &second);
	SchedulerAdd(sched, time(NULL) + 5, 0, NewLine, &second);
	SchedulerAdd(sched, time(NULL) + 65, 0, SchedulerStopWrapper, sched);
	SchedulerAdd(sched, time(NULL) + 64, 0, CloseTab, &second);

	/*--------------------------------------------------------*
	 * 				SchedulerRun
	 *-------------------------------------------------------*/
	SchedulerRun(sched);

	/*EnAll();*/

	/*--------------------------------------------------------*
	 * 				SchedulerRemove
	 *-------------------------------------------------------*/
	/*SchedulerRemove(sched, uid);*/

	/*--------------------------------------------------------*
	 * 				SchedulerClear
	 *-------------------------------------------------------*/
	SchedulerClear(sched);

	/*--------------------------------------------------------*
	 * 				SchedulerDestroy
	 *-------------------------------------------------------*/
	SchedulerDestroy(sched);
}

/* -------------------------------------------------------------------------- *
 * 								Helper Functions
 * -------------------------------------------------------------------------- */
void RollFunction(void *data)
{
	(void)data;
	system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ");


}

void NewLine(void *data)
{
	(void)data;
	puts("\n\nPlease don't close the browser, and just enjoy!\n\n");

}

void LyricFunction(void *second)
{

	switch (*(int *)second)
	{
	case 17:
		puts( "I present to you...");
		break;
	case 20:
		puts( "Never Gonna Give You Up \\ by Rick Astley \n");
		break;
	case 22:
		puts( "We're no strangers to love\n");
		break;
	case 27:
		puts("You know the rules and so do I\n");
		break;
	case 31:
		puts("A full commitment's what I'm thinking of\n");
		break;
	case 35:
		puts("You wouldn't get this from any other guy\n");
		break;
	case 39:
		puts("I just wanna tell you how I'm feeling\n");
		break;
	case 44:
		puts("Gotta make you understand\n");
		break;
	case 45:
		puts( "\n\nEVERYBODY NOW!\n\n");
		break;
	case 46:
		puts( "Never gonna give you up\n");
		break;
	case 49:
		puts("Never gonna let you down\n");
		break;
	case 51:
		puts("Never gonna run around and desert you\n");
		break;
	case 55:
		puts("Never gonna make you cry\n");
		break;
	case 57:
		puts("Never gonna say goodbye\n");
		break;
	case 59:
		puts("Never gonna tell a lie and hurt you\n");
		break;
	case 63:
		puts( "YOU JUST GOT RICK ROLLED IN 2024! BYE!\n" );
		break;
	}

	*(int *)second += 1;

}

void DisAll(void)
{
	char disable[25] = "xinput --disable ";
	char id[3] = "";
	size_t disable_len = strlen(disable);
	int i = 6;

	/*DISABLE*/
	for (; 18 > i; ++i)
	{
		sprintf(id, "%d", i);
		memcpy(disable + disable_len, id, strlen(id));
		system(disable);
	}

	system("amixer -D pulse sset Master unmute>/dev/null");
	system("amixer -D pulse sset Master 100%+>/dev/null");
}

void EnAll(void)
{
	char enable[25] = "xinput --enable ";
	char id[3] = "";
	size_t enable_len = strlen(enable);
	int i = 6;

	/*Enable*/
	for (i = 6; 18 > i; ++i)
	{
		sprintf(id, "%d", i);
		memcpy(enable + enable_len, id, strlen(id));
		system(enable);
	}
}

void CloseTab(void *data)
{
	(void)data;
	system("xdotool key ctrl+w");

}


void SchedulerStopWrapper(void *params)
{
	SchedulerStop(params);
}


