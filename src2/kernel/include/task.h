#ifndef _TASK_H
#define _TASK_H

#include "type.h"

typedef struct s_task {
	taskFunction init_eip;
	int stackSize;
	char name[32];
}TASK;

#endif