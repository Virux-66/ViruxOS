#include "type.h"
#include "process.h"
#include "global.h"
#include "prototype.h"
#include "important.h"

PRIVATE u32 va2la(int, u32);
PRIVATE u32 getSegBase_LDT(PCB* pPCB, int index);

PUBLIC void printxService(int unused1, int unused2, char* s, PCB* pPCB) {
	char ch;
	const char* p;

	if (intReEnterFlag == 0) {
		p = (char*)va2la(pPCB->processID, (u32)s);
	}
	else if (intReEnterFlag > 0) {
		p = s;
	}


	while ((ch = *p++) != 0) {
		putChar(ttyTable[pPCB->ttyIndex].pConsole, ch);
	}
}

PRIVATE u32 va2la(int pid, u32 offset) {
	PCB* pPCB = &PCBTable[pid];
	u32 segBase = getSegBase_LDT(pPCB, 1);
	u32 la = segBase + offset;
	return la;
}

PRIVATE u32 getSegBase_LDT(PCB* pPCB, int index) {
	Descriptor* pDesc = &pPCB->ldt[index];
	return (pDesc->baseHigh2 << 24 | pDesc->basehigh1 << 16 | pDesc->baseLow);
}