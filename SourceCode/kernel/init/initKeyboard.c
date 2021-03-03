#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void initKeyboard() {
	irqServiceTable[1] = keyboardService;
	enableIrq(1);
}