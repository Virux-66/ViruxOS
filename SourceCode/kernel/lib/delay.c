#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void delayInMilli(int milli_sec) {
	int t = getTicks();
	while (((getTicks() - t) * 1000 / 100) < milli_sec) {}
}