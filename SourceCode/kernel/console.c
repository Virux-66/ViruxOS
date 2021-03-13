#include	"type.h"
#include	"console.h"
#include	"global.h"
#include	"color.h"
#include	"prototype.h"
#include	"port.h"

PRIVATE void setCursor(unsigned int position);

PUBLIC int isCurrentConsole(CONSOLE* pConsole) {
	return (pConsole == &consoleTable[currentConsoleIndex]);
}

PUBLIC void putChar(CONSOLE* pConsole, char ch) {
	/*these c code write ascii into memory directly
	but the prerequisite is the base of ds is 0x00
	*/

	u8* pVmem = (u8*)(V_MEM_BASE + dispPos);	
	*pVmem = ch;
	pVmem++;
	*pVmem = DEFAULT_COLOR;
	pVmem++;
	dispPos += 2;

	setCursor(dispPos);
}

PRIVATE void setCursor(unsigned int position) {
	disableInt();
	writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_CURSOR_H);
	writePort(CRT_CONTROLLER_DATA_REGISTER, (position / 2) >> 8 & 0xFF);
	writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_CURSOR_L);
	writePort(CRT_CONTROLLER_DATA_REGISTER, (position / 2) & 0xFF);
	enableInt();
}