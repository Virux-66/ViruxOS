#include	"type.h"
#include	"console.h"
#include	"global.h"
#include	"color.h"
#include	"prototype.h"
#include	"port.h"
#include	"const.h"

PRIVATE void setCursor(unsigned int position);

PRIVATE void setScreenStartAddr(unsigned int startAddr);

PRIVATE void reset(CONSOLE* pConsole);

PUBLIC int isCurrentConsole(CONSOLE* pConsole) {
	return (pConsole == &consoleTable[currentConsoleIndex]);
}

PUBLIC void putChar(CONSOLE* pConsole, char ch) {// display char or string according to cursor, not dispPos
	/*these c code write ascii into memory directly
	but the prerequisite is the base of ds is 0x00
	*/

	u8* pVmem = (u8*)(V_MEM_BASE + pConsole->cursor*2);	
	switch (ch) {
	case '\n':
		if (pConsole->cursor < pConsole->originalAddr + pConsole->vMemLimit+SCREEN_WIDTH) {
			pConsole->cursor = pConsole->originalAddr + SCREEN_WIDTH * ((pConsole->cursor - pConsole->originalAddr) / SCREEN_WIDTH + 1);
		}
		break;
	case '\b':
		if (pConsole->cursor > pConsole->originalAddr) {
			pConsole->cursor--;
			*(pVmem - 2) = ' ';
			*(pVmem - 1) = DEFAULT_COLOR;
		}
		break;
	default:
		if(pConsole->cursor<pConsole->originalAddr+pConsole->vMemLimit-1){ 
			*pVmem = ch;
			pVmem++;
			*pVmem = DEFAULT_COLOR;
			pVmem++;
			pConsole->cursor++;
		}
		break;
	}
	if ((pConsole->cursor >= pConsole->currentStartAddr + SCREEN_SIZE) || (pConsole->cursor < pConsole->currentStartAddr)) {
		pConsole->currentStartAddr = ((pConsole->cursor - pConsole->originalAddr) / SCREEN_WIDTH) * SCREEN_WIDTH;
	}

	/*while (pConsole->cursor >= pConsole->currentStartAddr + SCREEN_SIZE) {
		scrollScreen(pConsole, SCR_UP);
	}*/
	reset(pConsole);
}

PUBLIC void initConsole(TTY* pTty) {
	int ttyIndex = pTty - ttyTable;
	pTty->pConsole = &consoleTable[ttyIndex];
	int vMemSize = V_MEM_SIZE >> 1;
	int consoleSize = vMemSize / consoleNumber;
	pTty->pConsole->originalAddr = ttyIndex * consoleSize;
	pTty->pConsole->vMemLimit = consoleSize;
	pTty->pConsole->currentStartAddr = pTty->pConsole->originalAddr;

	pTty->pConsole->cursor = pTty->pConsole->originalAddr;

	if (ttyIndex == 0) {
		pTty->pConsole->cursor = dispPos / 2;
		dispPos = 0;
	}
	else {
		putChar(pTty->pConsole, ttyIndex + '0');
		putChar(pTty->pConsole, '#');
	}
	setCursor(pTty->pConsole->cursor);// VGA just has only one cursor.
}

PUBLIC void switchOverConsole(int consoleIndex) {//0<=consoleIndex<consoleNumber
	if (consoleIndex < 0 || consoleIndex >= consoleNumber) {
		return;
	}
	currentConsoleIndex = consoleIndex;
	setCursor(consoleTable[consoleIndex].cursor * 2);
	setScreenStartAddr(consoleTable[consoleIndex].currentStartAddr);
}

PUBLIC void scrollScreen(CONSOLE* pConsole,int direction){
	if (direction == SCR_UP) {
		if (pConsole->currentStartAddr + SCREEN_SIZE < pConsole->originalAddr + pConsole->vMemLimit) {
			pConsole->currentStartAddr += SCREEN_WIDTH;
		}
	}
	if (direction == SCR_DW) {
		if (pConsole->currentStartAddr > pConsole->originalAddr) {
			pConsole->currentStartAddr -= SCREEN_WIDTH;
		}
	}
	setScreenStartAddr(pConsole->currentStartAddr);
	setCursor(pConsole->cursor*2);

}

PRIVATE void setScreenStartAddr(unsigned int startAddr) {
	disableInt();
	writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_START_ADDR_H);
	writePort(CRT_CONTROLLER_DATA_REGISTER, (startAddr>> 8) & 0xFF);
	writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_START_ADDR_L);
	writePort(CRT_CONTROLLER_DATA_REGISTER, startAddr & 0xFF);
	enableInt();
}

PRIVATE void setCursor(unsigned int position) {//position in byte
	disableInt();													
	writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_CURSOR_H);
	writePort(CRT_CONTROLLER_DATA_REGISTER, (position / 2) >> 8 & 0xFF);
	writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_CURSOR_L);
	writePort(CRT_CONTROLLER_DATA_REGISTER, (position / 2) & 0xFF);
	enableInt();
/*the reason why position is divided by 2 is CRT_CURSOR_H and CRT_CURSOR_L indicates the position of target character
and one character occupies two bytes.
*/
}

PRIVATE void reset(CONSOLE* pConsole) {
	setCursor(pConsole->cursor * 2);
	setScreenStartAddr(pConsole->currentStartAddr);
}