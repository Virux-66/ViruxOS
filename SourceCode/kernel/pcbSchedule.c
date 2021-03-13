#include "type.h"
#include "global.h"
#include "const.h"

PUBLIC void pcbSchedule() {
	PCBready++;
	if (PCBready >= PCBTable + processNumber) {
		PCBready = PCBTable;
	}
}