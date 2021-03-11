#ifndef _PROCESS_H_
#define _PROCESS_H_
#define processNumber 3
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
	u32 eip;//0x30cfa
	u32 cs;//0x05
	u32 eflags;
	u32 esp;//0x344c4
	u32 ss;//0x0d
}stackFrame;

typedef struct processControlBlock {
	stackFrame stackframe;
	u16 ldtSelector;		//this selector is connected to gdt
	Descriptor ldt[LDTSIZE]; //LDTSIZE defined in const.h  0x3c50a
	u32 processID;
	char processName[32];
}PCB;

#endif // !_PROCESS_H_

