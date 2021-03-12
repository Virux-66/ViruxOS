#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"
#include "port.h"
#include "keyboard.h"
#include "color.h"

PUBLIC void tty() {
	dispColorStr("T", WORD_RED);
	while (1) {
		keyboardResolution();
		disableInt();
		writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_CURSOR_H);
		writePort(CRT_CONTROLLER_DATA_REGISTER, (dispPos / 2) >> 8 & 0xFF);
		writePort(CRT_CONTROLLER_ADDRESS_REGISTER, CRT_CURSOR_L);
		writePort(CRT_CONTROLLER_DATA_REGISTER, (dispPos / 2)& 0xFF);
		enableInt();
	}
}
//0x08:0x30490
PUBLIC void keyProcess(u32 key) {
	char output[2] = { '\0','\0' };
	if (!(key & FLAG_EXT)){
		output[0] = key & 0xFF;
		dispStr(output);
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