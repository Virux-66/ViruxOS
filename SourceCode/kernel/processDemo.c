#include "type.h"
#include "prototype.h"
#include "global.h"

PUBLIC void TestA() {
	int i = 0;
	while (1) {
		printf("<Ticks:%x>",getTicks());
		delayInMilli(200);
	}
}

PUBLIC void TestB() {
	int i = 0x1000;
	while (1) {
		printf("B");
		delayInMilli(200);
	}
}

PUBLIC void TestC() {
	int i = 0x2000;
	while (1) {
		printf("C");
		delayInMilli(200);
	}
}