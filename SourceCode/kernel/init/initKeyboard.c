#include "type.h"
#include "global.h"
#include "prototype.h"
#include "keyboard.h"
#include "port.h"

PUBLIC KB_INPUT kb_in;

PRIVATE void waitBufEmpty();

PRIVATE void getAck();

PUBLIC void initKeyboard() {
	kb_in.count = 0;
	kb_in.pHead = kb_in.pTail = kb_in.buf;
	shift_l = shift_r = 0;
	alt_l = alt_r = 0;
	ctrl_l = ctrl_r = 0;
	caps_lock = 0;
	num_lock = 1;
	scroll_lock = 0;
	setled();
	irqServiceTable[1] = keyboardService;
	enableIrq(1);
}


PUBLIC void setled() {
	u8 led = (caps_lock << 2) | (num_lock << 1) | scroll_lock;
	waitBufEmpty();
	writePort(_8242_BUFFER_PORT, LED_CODE);
	getAck();
	waitBufEmpty();
	writePort(_8242_BUFFER_PORT, led);
	getAck();
}

PRIVATE void waitBufEmpty() {//read port 0x64, if its the 1th bit is 0 that means buf empty
	u8 code;
	do {
		code = readPort(_8242_CONTROL_PORT);
	} while (code & 0x02);
}
PRIVATE void getAck() {
	u8 code;
	do {
		code = readPort(_8242_BUFFER_PORT);
	} while (code != KB_ACK);
}