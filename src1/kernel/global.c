#define _GLOBAL_VARIABLE

#include "type.h"
#include "task.h"
#include "const.h"
#include "prototype.h"
#include "global.h"

PUBLIC TASK taskTable[taskNumber] = { {sys_tty,0x8000,"sys_tty"},{sys_task,0x8000,"sys_task"} };
							
PUBLIC TASK userProcessTable[userProcessNumber] = { {TestA,0x8000,"TestA"},
												{TestB,0x8000,"TestB"},
												{TestC,0x8000,"TestC"}   };
											
PUBLIC irqService irqServiceTable[16];

PUBLIC systemCall sysCallTable[sysCallNumber] = { getTicksService , writeService , printxService , sendrecService};

PUBLIC u8 processStack[processStackSize * (userProcessNumber+taskNumber)];

PUBLIC char string1[] = "Executing in kernel!";

PUBLIC char string2[] = "Executing in 32-bit protected Mode!";

PUBLIC char string3[] = "Paging has been set up, just direct mapping!";

PUBLIC char string4[] = "Initialize 8259A programmable interrupt control!";

PUBLIC char string5[] = "Initialize interrupt descriptor table(IDT)!";

PUBLIC char string6[] = "Start the first process: TextA!";

PUBLIC TTY ttyTable[consoleNumber];

PUBLIC CONSOLE consoleTable[consoleNumber];
