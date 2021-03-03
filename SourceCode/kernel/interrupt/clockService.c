#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void clockService(int irq) {
	ticks++;
	dispStr("INT 0x20 happen!\n");
	if (intReEnterFlag != 0) {
		dispStr("Interrupt re-enter");
	}
	PCBready++;
	if (PCBready >= PCBTable + processNumber)
		PCBready = PCBTable;
}



