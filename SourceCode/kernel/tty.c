#include "type.h"
#include "tty.h"
#include "prototype.h"
#include "keyboard.h"
#include "keymap.h"
#include "global.h"
#include "port.h"

#define TTY_FIRST ttyTable
#define TTY_END	  ttyTable+consoleNumber

PRIVATE void initTty(TTY* pTty);
PRIVATE void ttyRead(TTY* pTty);
PRIVATE void ttyWrite(TTY* pTty);

PUBLIC void tty() {
	TTY* pTty;
	for (pTty = TTY_FIRST; pTty < TTY_END; pTty++){
		initTty(pTty);
	}
	currentConsoleIndex = 0;	//global variable
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
		if (pTty->countBuf < TTY_BUF_BYTES) {//put char into tty buffer 
			*(pTty->pHead) = key;
			pTty->pHead++;
			pTty->countBuf++;
			if (pTty->pHead == pTty->inputBuf + TTY_BUF_BYTES)
				pTty->pHead = pTty->inputBuf;
		}
	}
	else {
		int rawCode = key & MASK_RAW;
		switch (rawCode) {
		case UP:
			if ((key & FLAG_SHIFT_L) || (key & FLAG_SHIFT_R)) {
				disableInt();
				writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_START_ADDR_H);
				writePort(CRT_CONTROLLER_DATA_REGISTER, ((80 * 15) >> 8) & 0xFF);
				writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_START_ADDR_L);
				writePort(CRT_CONTROLLER_DATA_REGISTER, (80 * 15) & 0xFF);
				enableInt();
			}
			break;
		case DOWN:
			if ((key & FLAG_SHIFT_L) || (key & FLAG_SHIFT_R)) {
				/* shift+Down do nothing*/
			}
			break;
		default:
			break;
		}
	}
}

PRIVATE void initTty(TTY* pTty) {
	pTty->countBuf = 0;
	pTty->pHead = pTty->pTail = pTty->inputBuf;
	int index = pTty - ttyTable;
	pTty->pConsole = consoleTable + index;
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