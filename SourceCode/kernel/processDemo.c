#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "global.h"

PUBLIC void TestA() {
	int i = 0;
	while (1) {
		dispStr("A");
		dispInt(i++);
		dispStr(".");
	}
}