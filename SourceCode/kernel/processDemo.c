#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"
#include "port.h"

PUBLIC void TestA() { //0x05:0x30e26
	int ocw1 = readPort(INT_8259A_MASTER_PORT2);
	dispInt(ocw1);
	int tick;
	tick= getTicks();
	dispInt(tick);
	int i = 0;
	while (1) {
		dispStr("A");
		dispInt(i++);
		dispStr(".");
		//delayInMilli(20);
	}
}
//process switching function not complete
PUBLIC void TestB() {
	int i = 0x1000;
	while (1) {
		dispStr("B");
		dispInt(i++);
		dispStr(".");
		//delayInMilli(20);
	}
}