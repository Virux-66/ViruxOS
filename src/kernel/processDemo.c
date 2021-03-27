#include "type.h"
#include "prototype.h"
#include "global.h"
#include "const.h"
#include "message.h"
#include "package.h"

PUBLIC int get_ticks();
PRIVATE int func(PACKAGE* pPackage, PCB* pPCB);

PUBLIC void TestA() {

	printf("In TestA now\n");
	PACKAGE pack;
	pack.source = 2;
	pack.destination = 1;
	pack.dataSize = 10;
	u32 seg_base1;
	u32 seg_base2;
	PCB* p1 = &PCBTable[2];
	PCB* p2 = &PCBTable[1];

	while (1) {

		seg_base1 = (p1->ldt[2]).baseHigh2 << 24 | (p1->ldt[2]).basehigh1 << 16 | (p1->ldt[2]).baseLow;
		seg_base2 = (p2->ldt[2]).baseHigh2 << 24 | (p2->ldt[2]).basehigh1 << 16 | (p2->ldt[2]).baseLow;

		printf("TestA=%d\n", seg_base1);
		printf("sys_task=%d\n", seg_base2);
		exchange(&pack);
		delayInMilli(10);
		seg_base1 = (p1->ldt[2]).baseHigh2 << 24 | (p1->ldt[2]).basehigh1 << 16 | (p1->ldt[2]).baseLow;
		seg_base2 = (p2->ldt[2]).baseHigh2 << 24 | (p2->ldt[2]).basehigh1 << 16 | (p2->ldt[2]).baseLow;
		//printf("TestA=%d\n", seg_base1);
		//printf("sys_task=%d\n", seg_base2);
		delayInMilli(3000);
	}
}

PUBLIC void TestB() {
	int i = 0x1000;
	while (1) {
		//printf("B");
		delayInMilli(3000);
	}
}

PUBLIC void TestC() {
	int i = 0x2000;
	while (1) {
		//printf("C");
		delayInMilli(3000);
	}
}

PUBLIC int get_ticks() {
	MESSAGE msg;
	resetMessage(&msg);
	msg.type = GET_TICKS;
	send_recv(BOTH, 1, &msg);
	return msg.u.m3.m3i1;
}
