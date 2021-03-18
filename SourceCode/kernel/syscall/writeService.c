#include "type.h"
#include "process.h"
#include "prototype.h"
#include "global.h"

PUBLIC int writeService(/*const*/ char* buf,int length,PCB* pPCB) {
	char* p = buf;
	int len = length;
	while (len) {
		putKeyIntoBuf(&ttyTable[pPCB->ttyIndex], *p);
		p++;
		len--;
	}
	return 0;
}