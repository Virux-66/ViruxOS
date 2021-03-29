#include "type.h"
#include "prototype.h"
#include "global.h"
#include "const.h"
#include "message.h"
#include "package.h"

PUBLIC int get_ticks();
PRIVATE int func(PACKAGE* pPackage, PCB* pPCB);
PRIVATE void dataProcess();

PUBLIC void TestA() {


	PACKAGE pack;
	int number = 422;
	printf("In TestA now\n");
	printf("<Ticks=%d>\n", getTicks());
	printf("Number=%d\n", number);
	for (int i = 0; i < number; i++) {
		ack = 0;
		pack.source = 2;
		pack.destination = 3;
		pack.dataSize = 128;
		exchange(&pack);
	}
	printf("<Ticks=%d>\n", getTicks());

	while (1) {
		delayInMilli(1);
	}
}

PUBLIC void TestB() {
	printf("In TestB!!!!!!!!!!!!!! now\n");
	while (!ack) {};


	dataProcess();





	/*MESSAGE msg;
	resetMessage(&msg);
	do {
		send_recv(RECEIVE, 1, &msg);
	} while (!(msg.type == SBEA));
	msg.source = 3;
	msg.dest = 1;
	msg.type = ECHO;
	send_recv(SEND, 1, &msg);*/

	while (1) {
		delayInMilli(1);
	}
}



PUBLIC int get_ticks() {
	MESSAGE msg;
	resetMessage(&msg);
	msg.type = GET_TICKS;
	send_recv(BOTH, 1, &msg);
	return 1;
}


PRIVATE void dataProcess() {

}