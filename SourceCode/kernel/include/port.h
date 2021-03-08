#ifndef _PORT_H



//8259A port
#define INT_8259A_MASTER_PORT1 0x20
#define INT_8259A_MASTER_PORT2 0x21
#define INT_8259A_SLAVE_PORT1 0xa0
#define INT_8259A_SLAVE_PORT2 0xa1

//8253 PIT:programmable interval timer
#define _8253_COUNTER0_PORT	0x40
#define _8253_COUNTER1_PORT	0x41
#define _8253_COUNTER2_PORT	0x42
#define _8253_MCR_PORT		0x43

#define _8242_BUFFER_PORT	0x60
#define _8242_CONTROL_PORT	0x64

#endif // !_PORT_H
