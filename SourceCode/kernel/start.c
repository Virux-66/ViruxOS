#include "type.h"
#include "important.h"
#include "prototype.h"
#include "global.h"
#include "const.h"

PUBLIC	void cstart() {
	//dispPos = 0;
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

	//dispStr(string1);
	dispPos = 1600;
	dispStr(string4);
	initialize8259A();
	initClock();
	initKeyboard();

	dispPos = 1760;
	dispStr(string5);
	initializeIDT();

	initializeTSS();
	tss.ss0 = SELECTOR_FLAT_RW;
	initializeLDT();
	initializePCB();

	dispPos = 1920;
	dispStr(string6);
	dispStr("\n");
	PCBready = PCBTable+1;

}

//0x9000:0x02d1
//0x08:0x3049a