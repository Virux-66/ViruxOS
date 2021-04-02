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
	int number = 80;
	printf("\nIn TestA now\n");
	printf("Test N-SBEA IPC algorithm!\n");
	printf("IPC number=%d\n",number);
	PACKAGE pack;
	pack.source = 2;
	pack.destination = 3;
	pack.dataSize = 2048;		//2KB
	negotiate(&pack);
	int ticks = getTicks();
	printf("<ticks=%d>\n", ticks);
	for (int i = 0; i < number; i++) {
		ack = 0;
		pack.source = 2;
		pack.destination = 3;
		pack.dataSize = 128;
		exchange(&pack);
	}
	printf("<ticks=%d>\n", getTicks()-ticks);
	printf("TestA has sent 3000 * 108B to TestB. It takes %d ticks!\n", getTicks() - ticks);





	while (1) {
		delayInMilli(1);
	}
}

PUBLIC void TestB() {
	printf("In TestB now!\n");
	while (!ack) {};


	dataProcess();



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