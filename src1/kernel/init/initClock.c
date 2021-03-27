#include "type.h"
#include "prototype.h"
#include "port.h"
#include "global.h"


#define HZ			100     //100hz 10ms per clock interrupt
#define TIMER_FREQ	1193182L
PUBLIC void initClock() {
	writePort(_8253_MCR_PORT,0x34);
	writePort(_8253_COUNTER0_PORT, (u8)(TIMER_FREQ / HZ));
	writePort(_8253_COUNTER0_PORT, (u8)((TIMER_FREQ / HZ) >> 8));
	irqServiceTable[0] = clockService;
	enableIrq(0);
}