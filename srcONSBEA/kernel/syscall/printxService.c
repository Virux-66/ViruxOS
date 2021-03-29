#include "type.h"
#include "process.h"
#include "global.h"
#include "prototype.h"
#include "important.h"
#include "const.h"
#include "color.h"



PUBLIC void printxService(int unused1, int unused2, char* s, PCB* pPCB) {
	char ch;
	const char* p;

	//char errInfo[] = "? k_reenter is incorrect for unknown reason";


	if (intReEnterFlag == 0) {
		p = (char*)va2la(pPCB->processID, (u32)s);
	}
	else if (intReEnterFlag > 0) {
		p = s;
	}



	if ((*p == MAG_CH_PANIC) || (*p == MAG_CH_ASSERT && PCBready < &PCBTable[taskNumber])) {
		disableInt();
		char* v = (char*)V_MEM_BASE;
		const char* q = p + 1;
		while (v < (char*)(V_MEM_BASE + V_MEM_SIZE)) {
			*v++ = *q++;
			*v++ = WORD_RED;
			if (!*q) {
				while (((int)v - V_MEM_BASE) % (SCREEN_WIDTH * 16)) {
					v++;
					*v++ = WORD_BROWN;
				}
				q = p + 1;
			}
			
		}
		__asm__ __volatile__("hlt");
	}












	while ((ch = *p++) != 0) {
		putChar(ttyTable[pPCB->ttyIndex].pConsole, ch);
	}
}


