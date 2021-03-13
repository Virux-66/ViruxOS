#ifndef _TYY_H

#include "type.h"
#include "console.h"

#define _TYY_H
#define TTY_BUF_BYTES	256

typedef struct s_tty {
	u32 inputBuf[TTY_BUF_BYTES];
	u32* pHead;
	u32* pTail;
	int countBuf;
	CONSOLE* pConsole;
}TTY;

#endif
