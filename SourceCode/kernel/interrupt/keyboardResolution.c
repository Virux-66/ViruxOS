#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"
#include "keyboard.h"
#include "keymap.h"

extern KB_INPUT kb_in;
PUBLIC void keyboardResolution() {
	u8 scanCode;
	char output[2];
	int make;
	memset(output, 0, 2);
	if (kb_in.count > 0){
		disableInt();
		scanCode = *(kb_in.pTail);
		kb_in.pTail++;
		if (kb_in.pTail == kb_in.buf + KB_IN_BYTES)
			kb_in.pTail = kb_in.buf;
		kb_in.count--;
		enableInt();
		
		if (scanCode == 0xE1) {

		}
		else if (scanCode == 0xE0) {

		}
		else {
			make = ( scanCode & 0x80 ? 0 : 1 );
			if (make) {
				output[0] = keymap[(scanCode & 0x7F) * MAP_COLS];
				dispStr(output);
			}
		}

	}

}
//why disable int?
//it's possible that when accessing kb_in, keyboard interrupt occurs
//if that so, kb_in will be changed in the middle of this process.
//kb_in is critical variable.