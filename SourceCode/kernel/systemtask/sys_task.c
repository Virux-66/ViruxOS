#include "type.h"
#include "prototype.h"
#include "const.h"

PUBLIC void sys_task() {
	MESSAGE meg;


	while (1) {
		send_recv(RECEIVE, ANY, &meg);
		int value = meg.u.m1.m1i1;
		printf("%d", value);

		delayInMilli(200);
	}
}