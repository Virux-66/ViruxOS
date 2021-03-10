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

/*PRIVATE int code_with_E0 = 0;
PRIVATE int shift_l ;
PRIVATE int shift_r ;
PRIVATE int alt_l = 0;
PRIVATE int alt_r = 0;
PRIVATE int ctrl_l = 0;
PRIVATE int ctrl_r = 0;
PRIVATE int caps_lock;
PRIVATE int num_lock;
PRIVATE int scroll_lock;
PRIVATE int column;*/

PUBLIC void keyboardResolution() {
	u8 scanCode;
	char output[2];
	int make;			//this variable is to decide if make code
	u32 key = 0;		//ascii in keymap.h
	u32* keyrow;

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
			keyrow = &keymap[(scanCode & 0x7F) * MAP_COLS];
			column = 0;
			if (shift_l || shift_r) {
				column = 1;
			}
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
				if (!make) {
					key = 0;
				}
				break;
			}
			if (key) {
				output[0] = key;
				dispStr(output);
			}
		}
	}
}
//why disable int?
//it's possible that when accessing kb_in, keyboard interrupt occurs
//if that so, kb_in will be changed in the middle of this process.
//kb_in is critical variable.