#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void initializePCB() {
	u16 selectorLDT = SELECTOR_LDT_FIRST;

	for (int i = 0; i < processNumber; i++) {
		PCB* pPCB = &PCBTable[i];
		TASK* task = &taskTable[i];

		pPCB->ldtSelector = selectorLDT;
		selectorLDT += 8;
		memcpy(&pPCB->ldt[0], &gdt[1], sizeof(Descriptor));
		pPCB->ldt[0].attr1 = DA_P | (PRIVILEGE_RING1 << 5) | DA_S | DA_C_X | DA_C_R;
		memcpy(&pPCB->ldt[1], &gdt[2], sizeof(Descriptor));
		pPCB->ldt[1].attr1 = DA_P | (PRIVILEGE_RING1 << 5) | DA_S | DA_D_0 | DA_D_W;
		//pPCB->ldt[1].limitHigh_attr2 =0xcf;
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
		pPCB->stackframe.gs = (SELECTOR_VIDEO-0x03) | SA_GDT | SA_RPL1;//!!
		pPCB->stackframe.fs = 0x00;
		pPCB->stackframe.fs = 0x08 | SA_LDT | SA_RPL1;
		pPCB->stackframe.eip = (u32)task->init_eip;
		pPCB->stackframe.esp = (u32)(processStack + processStackSize * i);

		pPCB->stackframe.eflags = 0x1202;
		pPCB->processID = i;
		memcpy(&pPCB->processName, &(task->name), sizeof(task->name));
	}
}