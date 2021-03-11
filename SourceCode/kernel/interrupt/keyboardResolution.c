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

extern KB_INPUT kb_in;		//defined in initKeyboard.c

PRIVATE u8 getByteFromKbuf();

PUBLIC void keyboardResolution() {
	u8 scanCode;
	int make;			//this variable is to decide if make code
	u32 key = 0;		//ascii in keymap.h
	u32* keyrow;

	if (kb_in.count > 0) {
		code_with_E0 = 0;
		scanCode = getByteFromKbuf();

		if (scanCode == 0xE1) {
			int i;
			u8 pausebrkScode[] = { 0xE1,0x1D,0x45,0xE1,0x9D,0xC5 };
			int isPausebreak = 1;
			for (i = 1; i < 6; i++) {
				if (getByteFromKbuf() != pausebrkScode[i]) {
					isPausebreak = 0;
					break;
				}
			}
			if (isPausebreak)
				key = PAUSEBREAK;
		}
		else if (scanCode == 0xE0) {
			scanCode = getByteFromKbuf();
			//printscreen is pressed
			if (scanCode == 0x2A) {
				if (getByteFromKbuf() == 0xE0) {
					if (getByteFromKbuf() == 0x37) {
						key = PRINTSCREEN;
						make = 1;
					}
				}
			}

			if (scanCode = 0xB7) {
				if (getByteFromKbuf() == 0xE0) {
					if (getByteFromKbuf() == 0xAA) {
						key = PRINTSCREEN;
						make = 0;
					}
				}
			}
			if (key = 0)
				code_with_E0 = 1;
		}
		if ((key != PAUSEBREAK) && (key != PRINTSCREEN)) {
			make = (scanCode & 0x80 ? 0 : 1);
			keyrow = &keymap[(scanCode & 0x7F) * MAP_COLS];
			column = 0;
			if (shift_l || shift_r)
				column = 1;
			if (code_with_E0) {
				column = 2;
				code_with_E0 = 0;
			}
			key = keyrow[column];
			switch (key) {
			case SHIFT_L:
				shift_l = make;
				key = 0;
				break;
			case SHIFT_R:
				shift_r = make;
				key = 0;
				break;
			case CTRL_L:
				ctrl_l = make;
				key = 0;
				break;
			case CTRL_R:
				ctrl_r = make;
				key = 0;
				break;
			case ALT_L:
				alt_l = make;
				key = 0;
				break;
			case ALT_R:
				alt_r = make;
				key = 0;
				break;
			default:
				if (!make)
					key = 0;
				break;
			}
			if (make) {
				key |= (shift_l ? FLAG_SHIFT_L : 0);
				key |= (shift_r ? FLAG_SHIFT_R : 0);
				key |= (ctrl_l ? FLAG_CTRL_L : 0);
				key |= (ctrl_r ? FLAG_CTRL_R : 0);
				key |= (alt_l ? FLAG_ALT_L : 0);
				key |= (alt_r ? FLAG_ALT_R : 0);
				keyProcess(make);
			}
		}
	}
}
PRIVATE u8 getByteFromKbuf() {
	u8 scanCode;
	while (kb_in.count <= 0) {} //infinite loop for next char;
	disableInt();
	scanCode = *(kb_in.pTail);
	kb_in.pTail++;
	if (kb_in.pTail == kb_in.buf + KB_IN_BYTES)
		kb_in.pTail = kb_in.buf;
	kb_in.count--;
	enableInt();
	return scanCode;
}



//why disable int?
//it's possible that when accessing kb_in, keyboard interrupt occurs
//if that so, kb_in will be changed in the middle of this process.
//kb_in is critical variable.