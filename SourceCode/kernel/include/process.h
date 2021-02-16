#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "type.h"
#include "const.h"
#include "important.h"

#define processNumber 1
#define processStackSize	0x8000

typedef struct stackframe {
	u32 gs;
	u32 fs;
	u32 es;
	u32 ds;
	u32 edi;
	u32 esi;
	u32 ebp;
	u32 kernel_esp;
	u32 ebx;
	u32 ecx;
	u32 edx;
	u32 eax;
	u32 retaddr;
	u32 eip;
	u32 cs;
	u32 eflags;
	u32 esp;
	u32 ss;
}stackFrame;

typedef struct processControlBlock {
	stackFrame stackframe;
	u16 ldtSelector;		//this selector is connected to gdt
	Descriptor ldt[LDTSIZE]; //LDTSIZE defined in const.h
	u32 processID;
	char processName[16];
}PCB;

#endif // !_PROCESS_H_

