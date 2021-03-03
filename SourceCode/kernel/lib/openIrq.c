#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void disableIrq(int irq) {
	if (irq < 8) {
		writePort(INT_8259A_MASTER_PORT2, readPort(INT_8259A_MASTER_PORT2) | (1 << irq));
	}
	else {
		writePort(INT_8259A_SLAVE_PORT2, readPort(INT_8259A_SLAVE_PORT2) | (1 << irq));
	}
}
PUBLIC void enableIrq(int irq) {
	if (irq < 8) {
		writePort(INT_8259A_MASTER_PORT2, readPort(INT_8259A_MASTER_PORT2) & (~(1 << irq)));
	}
	else {
		writePort(INT_8259A_SLAVE_PORT2, readPort(INT_8259A_SLAVE_PORT2) & (~(1 << irq)));
	}
}