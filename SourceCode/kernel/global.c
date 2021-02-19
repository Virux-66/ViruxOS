#define _GLOBAL_VARIABLE
#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "global.h"

PUBLIC TASK taskTable[taskNumber] = { {TestA,0x8000,"TestA"},
									{TestB,0x8000,"TestB"} };