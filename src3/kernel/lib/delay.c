#include "type.h"
#include "prototype.h"


PUBLIC void delayInMilli(int milli_sec) {
	int t = getTicks();
	while (((getTicks() - t) * 1000 / 100) < milli_sec) {}
}