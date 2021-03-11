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

PUBLIC void tty() {
	dispStr("T");
	while (1) {
		keyboardResolution();
	}
}

PUBLIC void keyProcess(u32 key) {
	char output[2] = { '\0','\0' };
	if (!(key & FLAG_EXT)){
		output[0] = key & 0xFF;
		dispStr(output);
	}
}