#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "const.h"
#include "type.h"
#include "important.h"
#include "message.h"

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

	int pFlags;				//0 = runnable 
							//=SENDING or RECEVING	blocked	

	MESSAGE* pMessage;		//for sender: it saves the message to send
							//for receiver: it is null ,containing no any data, pMessage=0
	u32 pReceivefrom;
	u32 pSendto;
	u32 hasIntMeg;			// 1=has interrupt message to handle;;;;0=dont have interrupt message;

	struct processControlBlock* sendingQueue;	//pcb that are ready to send message to this process

	struct processControlBlock* nextSending;	//next process in sending queue, one sender just can send message to one receiver at the same time;
	//There is no relationship between sendingQueue and nextSending.

	int ttyIndex;
	char processName[32];
}PCB;

#endif // !_PROCESS_H_

