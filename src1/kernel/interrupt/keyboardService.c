#include "type.h"
#include "keyboard.h"
#include "port.h"
#include "prototype.h"

extern KB_INPUT kb_in;		//defined in initKeyboard.c
//this handler just put inputed char into buffer
PUBLIC void keyboardService(int irq) {
	u8 scanCode = readPort(_8242_BUFFER_PORT);
	if (kb_in.count < KB_IN_BYTES) {
		*(kb_in.pHead) = scanCode;
		kb_in.pHead++;
		if (kb_in.pHead == kb_in.buf + KB_IN_BYTES)
			kb_in.pHead = kb_in.buf;
		kb_in.count++;
	}
}