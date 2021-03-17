#include "type.h"
#include "prototype.h"

PUBLIC void TestA() {
	int i = 0;
	dispStr("A");
	while (1) {
		//dispStr("A");
		delayInMilli(100);
	}
}

PUBLIC void TestB() {
	int i = 0x1000;
	dispStr("B");
	while (1) {
		//dispStr("B");
		delayInMilli(100);
	}
}

PUBLIC void TestC() {
	int i = 0x2000;
	dispStr("C");
	while (1) {
		//dispStr("B");
		delayInMilli(100);
	}
}