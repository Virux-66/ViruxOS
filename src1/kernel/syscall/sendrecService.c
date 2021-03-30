#include "const.h"
#include "type.h"
#include "process.h"
#include "message.h"
#include "prototype.h"
#include "global.h"

PUBLIC int sendrecService(int function, int src_dest, MESSAGE* pMessage, PCB* pPCB) {

	assert(intReEnterFlag == 0);
	assert((src_dest >= 0 && src_dest < taskNumber + userProcessNumber) || src_dest == ANY || src_dest == INTERRUPT);

	int result = 0;
	int caller = pPCB->processID;
	MESSAGE* la_message = (MESSAGE*)va2la(caller, pMessage);
	la_message->source = caller;
	assert(la_message->source != src_dest);

	if (function == SEND) {
		result = sendMessage(pPCB, src_dest, pMessage);
		if (result != 0)
			return result;
	}
	else if(function==RECEIVE){
		result = receiveMessage(pPCB, src_dest, pMessage);
		if (result != 0)
			return result;
	}
	else {
		panic("{sendrecService} invalid function:%d {SEND:%d, RECEIVE%d}.", function, SEND, RECEIVE);

	}
	return 0;
}