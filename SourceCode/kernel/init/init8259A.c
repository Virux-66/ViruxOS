#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"


//initialize 8259A ICW1~4 OCW1 IRQ0~15 service function
PUBLIC void initialize8259A() {
	writePort(INT_8259A_MASTER_PORT1, 0x11);	//ICW1
	writePort(INT_8259A_SLAVE_PORT1, 0x11);	//ICW1

	writePort(INT_8259A_MASTER_PORT2, 0x20);	//ICW2
	writePort(INT_8259A_SLAVE_PORT2, 0x28);	//ICW2

	writePort(INT_8259A_MASTER_PORT2, 0x04);	//ICW3
	writePort(INT_8259A_SLAVE_PORT2, 0x02);	//ICW3

	writePort(INT_8259A_MASTER_PORT2, 0x01);	//ICW4
	writePort(INT_8259A_SLAVE_PORT2, 0x01);	//ICW4

	writePort(INT_8259A_MASTER_PORT2, 0xfe);	//OCW1
	writePort(INT_8259A_SLAVE_PORT2, 0xff);	//OCW1

	for (int i = 0; i < 16; i++) {
		irqServiceTable[i] = spurious_irq;
	}
	irqServiceTable[0] = clockService;
}

PUBLIC void spurious_irq(int irq)
{
	dispStr("spurious_irq: ");
	dispInt(irq);
	dispStr("\n");
}