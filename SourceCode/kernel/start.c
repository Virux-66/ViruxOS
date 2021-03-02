#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"


PUBLIC	void cstart() {
	dispPos = 0;
	newDescIndex = 4;
	ticks = 0;
	memcpy(&gdt, (void*)(*((u32*)(&gdtPos[2]))), *((u16*)(&gdtPos[0]))+1);
	u16* limit = (u16*)(&gdtPos[0]);
	u32* base = (u32*)(&gdtPos[2]);
	*limit = GDTSIZE * sizeof(Descriptor) - 1;
	*base = (u32)&gdt;
	limit = (u16*)(&idtPos[0]);
	base = (u32*)(&idtPos[2]);
	*limit = IDTSIZE * sizeof(Gate) - 1;
	*base = (u32)&idt;
	initialize8259A();
	init8253();
	initializeIDT();
	initializeTSS();
	tss.ss0 = SELECTOR_FLAT_C;
	initializeLDT();
	initializePCB();
	PCBready = &PCBTable[0];
}

