#include "type.h"
#include "tty.h"
#include "keyboard.h"
#include "global.h"
#include "prototype.h"
#include "keymap.h"

extern KB_INPUT kb_in;		//defined in initKeyboard.c keyboard input buffer:public section

PRIVATE u8 getByteFromKbuf();

PUBLIC void keyboardResolution(TTY* pTty) {//standard resolution
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

			if (scanCode == 0xB7) {
				if (getByteFromKbuf() == 0xE0) {
					if (getByteFromKbuf() == 0xAA) {
						key = PRINTSCREEN;
						make = 0;
					}
				}
			}
			if (key == 0)
				code_with_E0 = 1;
		}
		if ((key != PAUSEBREAK) && (key != PRINTSCREEN)) {
			make = (scanCode & 0x80 ? 0 : 1);
			keyrow = &keymap[(scanCode & 0x7F) * MAP_COLS];
			column = 0;

			int caps = shift_l || shift_r;
			if (caps_lock) {
				if ((keyrow[0] >= 'a') && (keyrow[1] <= 'z'))
					caps = !caps;
			}
			if (caps) {
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
			case CAPS_LOCK:
				if (make) {
					caps_lock = !caps_lock;
					setled();
				}
			case NUM_LOCK:
				if (make) {
					num_lock = !num_lock;
					setled();
				}
			case SCROLL_LOCK:
				if (make) {
					scroll_lock = !scroll_lock;
					setled();
				}
			default:
				break;
			}
			if (make) {
				int pad = 0;
				if ((key >= PAD_SLASH) && (key <= PAD_9)) {
					pad = 1;
					switch (key) {
					case PAD_SLASH:
						key = '/';
						break;
					case PAD_STAR:
						key = '*';
						break;
					case PAD_MINUS:
						key = '-';
						break;
					case PAD_PLUS:
						key = '+';
						break;
					case PAD_ENTER:
						key = ENTER;
						break;
					default:
						if (num_lock && (key >= PAD_0) && (key <= PAD_9)) {
							key = key - PAD_0 + '0';
						}
						else if (num_lock && (key == PAD_DOT)) {
							key = '.';
						}
						else {
							switch (key) {
							case PAD_HOME:
								key = HOME;
								break;
							case PAD_END:
								key = END;
								break;
							case PAD_PAGEUP:
								key = PAGEUP;
								break;
							case PAD_PAGEDOWN:
								key = PAGEDOWN;
								break;
							case PAD_UP:
								key = UP;
								break;
							case PAD_DOWN:
								key = DOWN;
								break;
							case PAD_LEFT:
								key = LEFT;
								break;
							case PAD_RIGHT:
								key = RIGHT;
								break;
							case PAD_DOT:
								key = DELETE;
								break;
							default:
								break;
							}
						}
						break;
					}

				}
				key |= shift_l ? FLAG_SHIFT_L : 0;
				key |= shift_r ? FLAG_SHIFT_R : 0;
				key |= ctrl_l  ? FLAG_CTRL_L  : 0;
				key |= ctrl_r  ? FLAG_CTRL_R  : 0;
				key |= alt_l   ? FLAG_ALT_L   : 0;
				key |= alt_r   ? FLAG_ALT_R   : 0;
				key |= pad ? FLAG_PAD : 0;
				keyProcess(pTty,key);
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