#include "type.h"
#include "prototype.h"
#include "const.h"
#include "global.h"

PUBLIC void sys_task() {
	MESSAGE meg;


	while (1) {
		send_recv(RECEIVE, ANY, &meg);		//if no any other process sends message, sys_task block
		int src = meg.source;
		switch (meg.type) {
		case GET_TICKS:
			meg.u.m3.m3i1 = ticks;
			send_recv(SEND, src, &meg);
			break;
		default:
			//panic("unknown meg type");
			break;
		}

		
	}
}