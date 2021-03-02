#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"


PUBLIC int getTicksService() {
	dispStr("+");
	return ticks;
}