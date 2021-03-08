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