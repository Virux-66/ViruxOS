#ifndef _CONSOLE_H
#define _CONSOLE_H

typedef struct s_console {
	unsigned int currentStartAddr;
	unsigned int originalAddr;
	unsigned int vMemLimit;
	unsigned int cursor;
}CONSOLE;

#endif