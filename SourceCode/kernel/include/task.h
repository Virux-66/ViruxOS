#ifndef _TASK_H
#define _TASK_H

#define processkNumber 3
typedef struct s_task {
	taskFunction init_eip;
	int stackSize;
	char name[32];
}TASK;

#endif