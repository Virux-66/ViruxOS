#include "type.h"
#include "tty.h"
#include "prototype.h"
#include "keyboard.h"
#include "keymap.h"
#include "global.h"
#include "port.h"
#include "const.h"

#define TTY_FIRST ttyTable
#define TTY_END	  ttyTable+consoleNumber

PRIVATE void initTty(TTY* pTty);
PRIVATE void ttyRead(TTY* pTty);
PRIVATE void ttyWrite(TTY* pTty);

PUBLIC void sys_tty() {
	TTY* pTty;
	for (pTty = TTY_FIRST; pTty < TTY_END; pTty++){
		initTty(pTty);
	}
	switchOverConsole(0);
	//assert(0);
	while (1) {
		for (pTty = TTY_FIRST; pTty < TTY_END; pTty++) {
			ttyRead(pTty);
			ttyWrite(pTty);
		}
	}
}

PUBLIC void keyProcess(TTY* pTty,u32 key) {
	char output[2] = { '\0','\0' };
	if (!(key & FLAG_EXT)){
		putKeyIntoBuf(pTty, key);
	}
	else {
		int rawCode = key & MASK_RAW;
		switch (rawCode) {//scroll through the screen
		case ENTER:
			putKeyIntoBuf(pTty, '\n');
			break;
		case BACKSPACE:
			putKeyIntoBuf(pTty, '\b');
			break;
		case UP:
			if ((key & FLAG_SHIFT_L) || (key & FLAG_SHIFT_R)) {
				scrollScreen(pTty->pConsole, SCR_UP);
			}
			break;
		case DOWN:
			if ((key & FLAG_SHIFT_L) || (key & FLAG_SHIFT_R)) {
				scrollScreen(pTty->pConsole, SCR_DW);
			}
			break;
		case F1:
		case F2:
		case F3:
		case F4:
		case F5:
		case F6:
		case F7:
		case F8:
		case F9:
		case F10:
		case F11:
		case F12:
			//if ((key & FLAG_ALT_L) || (key & FLAG_ALT_R)) {
				switchOverConsole(rawCode - F1);
			//}
			break;

		default:
			break;
		}
	}
}

PRIVATE void initTty(TTY* pTty) {
	pTty->countBuf = 0;
	pTty->pHead = pTty->pTail = pTty->inputBuf;
	initConsole(pTty);

}

PRIVATE void ttyRead(TTY* pTty) {
	if (isCurrentConsole(pTty->pConsole)) {
		keyboardResolution(pTty);
	}
}

PRIVATE void ttyWrite(TTY* pTty) {
	if (pTty->countBuf) {
		char ch = *(pTty->pTail);
		pTty->pTail++;
		if (pTty->pTail == pTty->inputBuf + TTY_BUF_BYTES)
			pTty->pTail = pTty->inputBuf;
		pTty->countBuf--;
		putChar(pTty->pConsole, ch);
	}
}

PUBLIC void putKeyIntoBuf(TTY* pTty, u32 key) {
	if (pTty->countBuf < TTY_BUF_BYTES) {
		*(pTty->pHead) = key;
		pTty->pHead++;
		if (pTty->pHead == pTty->inputBuf + TTY_BUF_BYTES)
			pTty->pHead = pTty->inputBuf;
		pTty->countBuf++;
	}
}