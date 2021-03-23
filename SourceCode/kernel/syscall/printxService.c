#include "type.h"
#include "process.h"
#include "global.h"
#include "prototype.h"

PUBLIC void printxService(int unused1, int unused2, char* s, PCB* pPCB) {
	char ch;
	const char* p = s;
	while ((ch = *p++) != 0) {
		putChar(ttyTable[pPCB->ttyIndex].pConsole, ch);
	}
}