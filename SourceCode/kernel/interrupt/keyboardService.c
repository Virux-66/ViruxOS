#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "keyboard.h"
#include "global.h"


extern KB_INPUT kb_in;
//this handler just put inputed char into buffer
PUBLIC void keyboardService(int irq) {
	clear();
	u8 scanCode = readPort(_8242_BUFFER_PORT);
	if (kb_in.count < KB_IN_BYTES) {
		*(kb_in.pHead) = scanCode;
		kb_in.pHead++;
		if (kb_in.pHead == kb_in.buf + KB_IN_BYTES)
			kb_in.pHead = kb_in.buf;
		kb_in.count++;
	}
	keyboardResolution();
}