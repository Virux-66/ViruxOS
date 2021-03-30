#include "type.h"
#include "global.h"
#include "prototype.h"


PUBLIC void clockService(int irq) {
	ticks++;
	//dispStr("INT 0x20 happen!\n");
	if (intReEnterFlag != 0) {
		//dispStr("Interrupt re-enter");
	}
	pcbSchedule();




	/*PCBready++;
	if (PCBready >= PCBTable + processNumber)
		PCBready = PCBTable;*/
}



