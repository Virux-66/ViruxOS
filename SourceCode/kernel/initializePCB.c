#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "global.h"


PUBLIC void initializePCB() {
	u16 selectorLDT = SELECTOR_LDT_FIRST;

	for (int i = 0; i < processNumber; i++) {
		PCB* pPCB = &PCBTable[i];
		pPCB->ldtSelector = selectorLDT;
		memcpy(&pPCB->ldt[0], &gdt[1], sizeof(Descriptor));
		pPCB->ldt[0].attr1 = DA_P | (PRIVILEGE_RING1 << 5) | DA_S | DA_C_X | DA_C_R;
		memcpy(&pPCB->ldt[1], &gdt[2], sizeof(Descriptor));
		pPCB->ldt[1].attr1 = DA_P | (PRIVILEGE_RING1 << 5) | DA_S | DA_D_0;
		//initialize segment register,selector connected to LDT
		pPCB->stackframe.cs = 0x00;
		pPCB->stackframe.cs = SA_LDT | SA_RPL1;
		pPCB->stackframe.ds = 0x00;
		pPCB->stackframe.ds = 0x08 | SA_LDT | SA_RPL1;
		pPCB->stackframe.es = 0x00;
		pPCB->stackframe.es = 0x08 | SA_LDT | SA_RPL1;
		pPCB->stackframe.ss = 0x00;
		pPCB->stackframe.ss = 0x08 | SA_LDT | SA_RPL1;
		pPCB->stackframe.gs = 0x00;
		pPCB->stackframe.gs = 0x08 | SA_LDT | SA_RPL1;
		pPCB->stackframe.fs = 0x00;
		pPCB->stackframe.fs = 0x08 | SA_LDT | SA_RPL1;
		pPCB->stackframe.eip = (u32)TestA;
		pPCB->stackframe.esp=(u32)processStack[i] + sizeof(processStack[i]);
		pPCB->stackframe.eflags = 0x1202;
		//pPCB->processName = "TestA";
	}
}