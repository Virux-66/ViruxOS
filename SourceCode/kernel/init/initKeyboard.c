#include "type.h"
#include "global.h"
#include "prototype.h"
#include "keyboard.h"

PUBLIC KB_INPUT kb_in;
PUBLIC void initKeyboard() {
	kb_in.count = 0;
	kb_in.pHead = kb_in.pTail = kb_in.buf;
	shift_l = shift_r = 0;
	irqServiceTable[1] = keyboardService;
	enableIrq(1);
}