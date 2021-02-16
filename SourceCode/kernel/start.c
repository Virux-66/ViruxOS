#include "type.h"
#include "const.h"
#include "important.h"
#include "process.h"
#include "global.h"
#include "prototype.h"

PUBLIC	void cstart() {
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
	initializeIDT();
	//initialize TSS descriptor and LDT descriptor in GDT
	initializeTSS();
	intializeLDT();
	intializePCB();
	PCBready = &PCBTable[0];
}

