#include "type.h"
#include "prototype.h"
#include "global.h"
#include "const.h"
#include "message.h"
#include "package.h"

PUBLIC int get_ticks();
PRIVATE int func(PACKAGE* pPackage, PCB* pPCB);
PRIVATE void dataProcess(MESSAGE* pMessage);

PUBLIC void TestA() {
	int ticks = 0;

	int index = 0;
	printf("In TestA now\n");
	MESSAGE msg;
	ticks = getTicks();
	printf("tick1=%d\n", ticks);
	for (; index < 100; index++) {
		resetMessage(&msg);
		msg.u.m1.m1i1 = 100;
		msg.source = 2;
		msg.dest = 3;
		msg.type = COPY;
		send_recv(SEND, 1, &msg);
		do {
			send_recv(RECEIVE, 1, &msg);
		} while (!msg.reply);
	}
	ticks = getTicks();
	printf("tick2=%d\n", ticks);
	while (1) {

		delayInMilli(1);
	}
}

PUBLIC void TestB() {

	printf("In TestB now\n");
	MESSAGE msg;
	MESSAGE response;
	while (1) {
		resetMessage(&msg);
		resetMessage(&response);
		do {
			send_recv(RECEIVE, 1, &msg);
		} while (!(msg.type==COPY));
		//printf("message=%d\n", msg.u.m1.m1i1);s
		response.source = 3;
		response.dest = 1;
		response.type = ECHO;
		send_recv(SEND, 1, &response);
		dataProcess(&msg);
	}


	while (1) {
		
		delayInMilli(1);
	}
}



PUBLIC int get_ticks() {
	MESSAGE msg;
	resetMessage(&msg);
	msg.type = GET_TICKS;
	send_recv(BOTH, 1, &msg);
	return msg.u.m3.m3i1;
}


PRIVATE void dataProcess(MESSAGE* pMessage) {

}