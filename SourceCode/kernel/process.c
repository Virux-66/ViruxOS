#include "type.h"
#include "global.h"
#include "const.h"
#include "process.h"
#include "important.h"
#include "message.h"
#include "prototype.h"
#include "assert.h"

PRIVATE void block(PCB* pPCB);
PRIVATE void unblock(PCB* pPCB);
PRIVATE int deadlock(int src, int dest);
PUBLIC int sendMessage(PCB* current, int dest, MESSAGE* m);
PUBLIC int receiveMessage(PCB* current, int src, MESSAGE* m);

PUBLIC void pcbSchedule() {
	PCBready++;
	if ((PCBready >= PCBTable + userProcessNumber+taskNumber) && (PCBready->pFlags==0)) {
		PCBready = PCBTable;
	}
}

PUBLIC u32 getSegBase_LDT(PCB* pPCB, int index) {
	Descriptor* pDesc = &pPCB->ldt[index];
	return (pDesc->baseHigh2 << 24 | pDesc->basehigh1 << 16 | pDesc->baseLow);
}

PUBLIC u32 va2la(int pid, u32 offset) {
	PCB* pPCB = &PCBTable[pid];
	u32 segBase = getSegBase_LDT(pPCB, 1);
	u32 la = segBase + offset;
	return la;
}

PUBLIC void resetMessage(MESSAGE* pMessage) {
	memset(pMessage, 0, sizeof(MESSAGE));
}

PUBLIC int send_recv(int function, int src_dest, MESSAGE* pMessage) {
	
	int result = 0;
	if (function == RECEIVE)
		memset(pMessage, 0, sizeof(MESSAGE));
	switch (function) {
	case BOTH:
		result = sendrec(SEND, src_dest, pMessage);
		if (result == 0) {
			result = sendrec(RECEIVE, src_dest, pMessage);
		}
		break;
	case SEND:
	case RECEIVE:
		result = sendrec(function, src_dest, pMessage);
		break;
	default:
		assert((function == BOTH) || (function == SEND) || (function == RECEIVE));
		break;
	}
	return result;
}



PRIVATE void block(PCB* pPCB) {
	assert(pPCB->pFlags);
	pcbSchedule();
}

PRIVATE void unblock(PCB* pPCB) {
	assert(pPCB->pFlags == 0);
}

//@return zero = no deadlock  nonzero=deadlock exit
PRIVATE int deadlock(int src, int dest) {//src and dest=processIndex
	PCB* pPCB = PCBTable+dest;
	while (1) {
		if (pPCB->pFlags & SENDING) {
			if (pPCB->pSendto == src) {
				pPCB = PCBTable+dest;
				printf("=_=%s", pPCB->processName);
				do {
					assert(pPCB->pMessage);
					pPCB = PCBTable + pPCB->pSendto;
					printf("->%s", pPCB->processName);
				} while (pPCB != PCBTable + src);
				printf("=_=");
				return 1;
			}
			pPCB = PCBTable + pPCB->pSendto;
		}
		else{
			break;
		}
	}
	return 0;
}


/*<Ring 0>Send a message to the dest proc. If dest is blocked waiting for 
the message, copy the message to it and unblock dest. Otherwise the caller
will be blocked and appended to the dest's sending queue.
@param current The caller, the sender
@param dest		to whom the message is sent
@param m		The message
@return		zero if success.
*/
PUBLIC int sendMessage(PCB* current, int dest, MESSAGE* m) {
	PCB* sender = current;
	PCB* receiver = PCBTable + dest;
	assert(sender->processID != dest);
	if (deadlock(sender->processID, dest)) {
		panic(">>DEADLOCK<<%s->%s", sender->processName, receiver->processName);
	}
	//receiver must be waiting for message from other processes.
	if ((receiver->pFlags & RECEVING) && (receiver->pReceivefrom == sender->processID || receiver->pReceivefrom == ANY)) {
		assert(receiver->pMessage);//receiver's message must not be empty and must point an address so that it can be put data.
		assert(m);				   //m is sending message sent by sender, also ,it cant be empty.
		memcpy(va2la(dest, (u32)receiver->pMessage), va2la(sender->processID, (u32)m), sizeof(MESSAGE));//this statement costs a majority of time of IPC
		receiver->pMessage = 0;//why pMessage becomes null?
		receiver->pFlags &= ~RECEVING;//Normally, receiver->pFlags will be 0-runnable
		receiver->pReceivefrom = NO_TASK;
		unblock(receiver);

		assert(receiver->pFlags == 0);
		assert(receiver->pMessage == 0);
		assert(receiver->pReceivefrom == NO_TASK);
		assert(receiver->pSendto == NO_TASK);
		assert(sender->pFlags == 0);
		assert(sender->pMessage == 0);
		assert(sender->pReceivefrom == NO_TASK);
		assert(sender->pSendto == NO_TASK);

	}
	else {//dest is not waiting for the msg
		sender->pFlags |= SENDING;//Normally sender->pFlags become SENDING from zero, which will be blocked.
		assert(sender->pFlags == SENDING);
		sender->pSendto = dest;
		sender->pMessage = m;
		
		if (receiver->sendingQueue) {
			PCB* temp;
			temp = receiver->sendingQueue;
			while (temp->nextSending)
				temp = temp->nextSending;
			temp->nextSending = sender;
		}
		else {//no other processes are ready to send message to receiver.
			receiver->sendingQueue = sender;
		}
		sender->nextSending = 0;//??????
		block(sender);

		assert(sender->pFlags == SENDING);
		assert(sender->pMessage != 0);
		assert(sender->pReceivefrom == NO_TASK);
		assert(sender->pSendto == dest);
	}
	return 0;
}

//zero if success
PUBLIC int receiveMessage(PCB* current, int src, MESSAGE* m) {
	PCB* p_who_wanna_recv = current;
	PCB* sender = 0;
	PCB* previous = 0;
	int copyok = 0;
	assert(p_who_wanna_recv->processID != src);
	if ((p_who_wanna_recv->hasIntMeg) && ((src == ANY) || (src == INTERRUPT))) {
		MESSAGE msg;
		resetMessage(&msg);
		msg.source = INTERRUPT;
		msg.type = HARD_INT;
		assert(m);
		memcpy(va2la(p_who_wanna_recv->processID, (u32)m), &msg, sizeof(MESSAGE));

		assert(p_who_wanna_recv->pFlags == 0);
		assert(p_who_wanna_recv->pMessage == 0);
		assert(p_who_wanna_recv->pSendto == NO_TASK);
		assert(p_who_wanna_recv->hasIntMeg == 0);
		return 0;
	}
	if (src == ANY) {//receiver is ready to receive message from any processes.
		if (p_who_wanna_recv->sendingQueue) { //receiver's queue is not empty
			sender = p_who_wanna_recv->sendingQueue;
			copyok = 1;

			assert(p_who_wanna_recv->pFlags == 0);
			assert(p_who_wanna_recv->pMessage == 0);//receiver's pMessage must be empty. the variable m is not the receiver's pMessage
			assert(p_who_wanna_recv->pReceivefrom == NO_TASK);
			assert(p_who_wanna_recv->pSendto == NO_TASK);
			assert(p_who_wanna_recv->sendingQueue != 0);
			assert(sender->pFlags == SENDING);
			assert(sender->pMessage != 0);
			assert(sender->pReceivefrom == NO_TASK);
			assert(sender->pSendto == p_who_wanna_recv->processID);
		}
	}
	else {//receiver is ready to receive message from a certain process.
		sender = PCBTable + src;
		if ((sender->pFlags & SENDING) && (sender->pSendto == p_who_wanna_recv->processID)) {
			copyok = 1;
			PCB* temp = p_who_wanna_recv->sendingQueue;
			assert(temp);
			while (temp) {
				assert(sender->pFlags & SENDING);
				if (temp->processID == src) {
					sender = temp;
					break;
				}
				previous = temp;
				temp = temp->nextSending;
			}
			assert(p_who_wanna_recv->pFlags == 0);
			assert(p_who_wanna_recv->pMessage == 0);
			assert(p_who_wanna_recv->pReceivefrom == NO_TASK);
			assert(p_who_wanna_recv->pSendto == NO_TASK);
			assert(p_who_wanna_recv->sendingQueue != 0);
			assert(sender->pFlags == SENDING);
			assert(sender->pMessage != 0);
			assert(sender->pReceivefrom == NO_TASK);
			assert(sender->pSendto == p_who_wanna_recv);
		}
	}
	if (copyok) {
		if (sender == p_who_wanna_recv->sendingQueue) {
			assert(previous == 0);
			p_who_wanna_recv->sendingQueue = sender->nextSending;
			sender->nextSending = 0;
		}
		else {
			assert(previous);
			previous->nextSending = sender->nextSending;
			sender->nextSending = 0;
		}

		assert(m);
		assert(sender->pMessage);

		memcpy(va2la(p_who_wanna_recv->processID, (u32)m), va2la(sender->processID, sender->pMessage), sizeof(MESSAGE));//this statement costs a majority of time of IPC

		sender->pMessage = 0;
		sender->pSendto = NO_TASK;
		sender->pFlags &= ~SENDING;//normally, sender->pFlags=0 , runnable
		unblock(sender);
	}
	else {//no any processes is sending any msg
		  //set pFlags=RECEVING so that p_who_wanna_recv will not be scheduled until it is unblocked.
	
		p_who_wanna_recv->pFlags |= RECEVING;	//receiver  is blocking
		p_who_wanna_recv->pMessage = m;
		if (src == ANY)
			p_who_wanna_recv->pReceivefrom = ANY;
		else
			p_who_wanna_recv->pReceivefrom = sender->processID;
		
		block(p_who_wanna_recv);

		assert(p_who_wanna_recv->pFlags == RECEVING);
		assert(p_who_wanna_recv->pMessage != 0);
		assert(p_who_wanna_recv->pReceivefrom != NO_TASK);
		assert(p_who_wanna_recv->pSendto != NO_TASK);
		assert(p_who_wanna_recv->hasIntMeg == 0);
	
	}
	return 0;
}