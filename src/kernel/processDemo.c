#include "type.h"
#include "prototype.h"
#include "global.h"
#include "const.h"
#include "message.h"

PUBLIC int get_ticks();

PUBLIC void TestA() {

	printf("In TestA now\n");
	while (1) {
		int tick = get_ticks();
		printf("<Ticks:%d>", tick);
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

PUBLIC int get_ticks() {
	MESSAGE msg;
	resetMessage(&msg);
	msg.type = GET_TICKS;
	send_recv(BOTH, 1, &msg);
	return msg.u.m3.m3i1;
}