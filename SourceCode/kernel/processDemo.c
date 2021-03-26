#include "type.h"
#include "prototype.h"
#include "global.h"
#include "const.h"
#include "message.h"

PUBLIC void TestA() {

	MESSAGE* pMessage;
	MESSAGE msg;
	pMessage = &msg;
	pMessage->type = 5;
	(pMessage->u).m1.m1i1 = 66;
	int result=send_recv(SEND, 1, pMessage);
	printf("%d\n", result);

	while (1) {
		//printf(PCBTable[1].processName);
		delayInMilli(200);
	}
}

PUBLIC void TestB() {
	int i = 0x1000;
	while (1) {
		//printf("B");
		delayInMilli(200);
	}
}

PUBLIC void TestC() {
	int i = 0x2000;
	while (1) {
		//printf("C");
		delayInMilli(200);
	}
}