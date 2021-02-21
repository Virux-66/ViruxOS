#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void initializeDescriptor(Descriptor* pointer, u32 base, u32 limit,u16 attribute) {
	pointer->limitLow = limit & 0xffff;
	pointer->baseLow = base & 0xffff;
	pointer->basehigh1 = (base >> 16) & 0xff;
	pointer->attr1 = attribute & 0xff;
	pointer->limitHigh_attr2 = ((limit >> 16) & 0x0f) | ((attribute >> 8) & 0xf0);
	pointer->baseHigh2 = (base >> 24) & 0xff;
}