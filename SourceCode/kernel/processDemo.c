#include "type.h"
#include "prototype.h"

PUBLIC void TestA() {
	int i = 0;
	while (1) {
		dispStr("A");
		dispInt(i++);
		dispStr(".");
	}
}