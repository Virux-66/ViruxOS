#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

//clock interrupt: 0x08:0x31232
PUBLIC void delay() {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 1000; k++) {}
		}
	}
}

PUBLIC void TestA() { //0x05:0x30e26
	int tick;
	tick= getTicks();
	dispInt(tick);

	int i = 0;
	while (1) {
		dispStr("A");
		dispInt(i++);
		dispStr(".");
	}
}
PUBLIC void TestB() {
	int i = 0x1000;
	while (1) {
		dispPos = 0;
		dispStr("B");
		dispInt(i++);
		dispStr(".");
		delay();
	}
}