#ifndef _CONSOLE_H
#define _CONSOLE_H

typedef struct s_console {// all struct variable is in word
	unsigned int currentStartAddr;
	unsigned int originalAddr;
	unsigned int vMemLimit;
	unsigned int cursor;
}CONSOLE;

#define SCR_UP			 1

#define SCR_DW			-1

#define SCREEN_SIZE		80*25

#define SCREEN_WIDTH	 80

#endif