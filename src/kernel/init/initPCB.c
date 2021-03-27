#include "type.h"
#include "important.h"
#include "const.h"
#include "process.h"
#include "task.h"
#include "prototype.h"
#include "global.h"


PUBLIC void initializePCB() {
	u16 selectorLDT = SELECTOR_LDT_FIRST;
	PCB*  pPCB;
	TASK* pTask;
	u8 descPrivilege;
	u8 rpl;
	int eflags;

	for (int i = 0; i < taskNumber + userProcessNumber; i++) {
		pPCB = PCBTable + i;
		if (i < taskNumber){
			pTask = taskTable + i;
			descPrivilege = PRIVILEGE_RING1;
			rpl = PRIVILEGE_RING1;
			eflags = 0x1202;
		}
		else {

			pTask = userProcessTable + i-taskNumber;
			descPrivilege = PRIVILEGE_RING3;
			rpl = PRIVILEGE_RING3;
			eflags = 0x202;
		}
		pPCB->ttyIndex = 0;

		memcpy(pPCB->processName, pTask->name, sizeof(pTask->name));
		pPCB->processID = i;
		pPCB->ldtSelector = selectorLDT;
		memcpy(&pPCB->ldt[0], &gdt[1], sizeof(Descriptor));
		pPCB->ldt[0].attr1 = DA_P | (descPrivilege << 5) | DA_S | DA_C_X | DA_C_R|DA_C_C;
		memcpy(&pPCB->ldt[1], &gdt[2], sizeof(Descriptor));
		pPCB->ldt[1].attr1 = DA_P | (descPrivilege << 5) | DA_S | DA_D_0 | DA_D_W;

		memcpy(&pPCB->ldt[2], &gdt[2], sizeof(Descriptor));
		pPCB->ldt[2].attr1 = DA_P | (descPrivilege << 5) | DA_S | DA_D_0 | DA_D_W;
		pPCB->ldt[2].limitHigh_attr2 &= 0x0F;
		pPCB->ldt[2].limitLow = 128;

		if (i == 1) {
			(pPCB->ldt[2]).baseLow = 1;
		}
		if (i == 2) {
			(pPCB->ldt[2]).baseLow = 2;
		}





		pPCB->stackframe.cs = SA_LDT | rpl;

		pPCB->stackframe.ds = 0x08 | SA_LDT | rpl;

		pPCB->stackframe.es = 0x08 | SA_LDT | rpl;

		pPCB->stackframe.ss = 0x08 | SA_LDT | rpl;

		pPCB->stackframe.gs = (SELECTOR_VIDEO-0x03) | SA_GDT | rpl;
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		pPCB->stackframe.fs = 0x10 | SA_LDT | rpl;				//fs points to ldt[2]

		pPCB->stackframe.eip = (u32)pTask->init_eip;
		pPCB->stackframe.esp = (u32)(processStack + processStackSize * (userProcessNumber+taskNumber-i));

		pPCB->stackframe.eflags = eflags;
		
		pPCB->pFlags = 0;
		pPCB->pMessage = 0;
		pPCB->pReceivefrom = NO_TASK;
		pPCB->pSendto = NO_TASK;
		pPCB->hasIntMeg = 0;
		pPCB->sendingQueue = 0;
		pPCB->nextSending = 0;





		pPCB++;
		pTask++;
		selectorLDT += 8;
	}
	memcpy(PCBTable[taskNumber].processName, "TestA", sizeof("TestA") - 1);
	memcpy(PCBTable[taskNumber + 1].processName, "TestB", sizeof("TestB") - 1);
	memcpy(PCBTable[taskNumber + 2].processName, "TestC", sizeof("TestC") - 1);




	/*
	PCBTable[1].ttyIndex = 0;
	PCBTable[2].ttyIndex = 1;
	PCBTable[3].ttyIndex = 2;
	*/
}