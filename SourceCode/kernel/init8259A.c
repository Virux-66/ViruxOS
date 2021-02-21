#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void initialize8259A() {
	writePort(INT_8259A_MASTER_PORT1, 0x11);	//ICW1
	writePort(INT_8259A_SLAVE_PORT1, 0x11);	//ICW1

	writePort(INT_8259A_MASTER_PORT2, 0x20);	//ICW2
	writePort(INT_8259A_SLAVE_PORT2, 0x28);	//ICW2

	writePort(INT_8259A_MASTER_PORT2, 0x04);	//ICW3
	writePort(INT_8259A_SLAVE_PORT2, 0x02);	//ICW3

	writePort(INT_8259A_MASTER_PORT2, 0x01);	//ICW4
	writePort(INT_8259A_SLAVE_PORT2, 0x01);	//ICW4

	writePort(INT_8259A_MASTER_PORT2, 0x00);	//OCW1
	writePort(INT_8259A_SLAVE_PORT2, 0x00);	//OCW1
}