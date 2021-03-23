#ifndef _CONST_H_
#define _CONST_H
#define	GDTSIZE		128
#define IDTSIZE		256
#define LDTSIZE		2

#define MASTER_INT_NUM 0x20
#define SLAVE_INT_NUM 0x28

#define userProcessNumber 3

#define processStackSize	0x8000

#define taskNumber	1

#define consoleNumber 3

#define sysCallNumber 3

#define V_MEM_BASE			0xB8000
#define V_MEM_SIZE			0x8000
#endif // !_CONST_H_
