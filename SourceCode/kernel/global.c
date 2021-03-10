#define _GLOBAL_VARIABLE
#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"


PUBLIC TASK taskTable[taskNumber]= { {TestA,0x8000,"TestA"},
									{TestB,0x8000,"TestB"} };
PUBLIC irqService irqServiceTable[16];

PUBLIC systemCall sysCallTable[16] = { getTicksService };// = {getTicksService};

PUBLIC u8 processStack[processStackSize * processNumber];

PUBLIC char string1[] = "Executing in kernel!";

PUBLIC char string2[] = "Executing in 32-bit protected Mode!";

PUBLIC char string3[] = "Paging has been set up, just direct mapping!";

PUBLIC char string4[] = "Initialize 8259A programmable interrupt control!";

PUBLIC char string5[] = "Initialize interrupt descriptor table(IDT)!";

PUBLIC char string6[] = "Start the first process: TextA!";
