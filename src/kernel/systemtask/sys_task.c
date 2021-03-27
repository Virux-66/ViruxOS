#include "type.h"
#include "prototype.h"
#include "const.h"
#include "global.h"
#include "package.h"

PUBLIC void sys_task() {
	MESSAGE msg;


	while (1) {
		send_recv(RECEIVE, ANY, &msg);		//if no any other process sends message, sys_task block
		int src = msg.source;
		switch (msg.type) {
		case GET_TICKS:
			msg.u.m3.m3i1 = ticks;
			send_recv(SEND, src, &msg);
			break;
		case SEG_EXC: {
			PACKAGE* pPack = msg.pPackage;

			PCB* pSource = PCBTable + pPack->source;
			PCB* pDest = PCBTable + pPack->destination;

			u32 seg_base = ((pSource->ldt[2]).baseHigh2) << 24 | (pSource->ldt[2]).basehigh1 << 16 | (pSource->ldt[2]).baseLow;
			pSource->ldt[2].baseHigh2 = pDest->ldt[2].baseHigh2;
			pSource->ldt[2].basehigh1 = pDest->ldt[2].basehigh1;
			pSource->ldt[2].baseLow = pDest->ldt[2].baseLow;
			pDest->ldt[2].baseHigh2 = (u8)seg_base >> 24;
			pDest->ldt[2].basehigh1 = (u8)seg_base >> 16;
			pDest->ldt[2].baseLow = (u16)seg_base;
			msg.reply = 1;
			send_recv(SEND, src, &msg);
			break;
		}
		default:
			//panic("unknown meg type");
			break;
		}

		
	}
}