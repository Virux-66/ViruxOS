#include "const.h"
#include "type.h"
#include "message.h"
#include "process.h"
#include "package.h"
#include "prototype.h"

PUBLIC int exchangeService(PACKAGE* pPackage,PCB* pPCB) {
	MESSAGE msg;
	resetMessage(&msg);
	msg.type = SEG_EXC;
	msg.pPackage = pPackage;
	int result=send_recv(SEND, 1, &msg);
	return result;
}

