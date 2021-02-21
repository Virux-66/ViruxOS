#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"
PUBLIC void TestA() { //0x05:0x30d01
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
		dispStr("B");
		dispInt(i++);
		dispStr(".");
	}
}