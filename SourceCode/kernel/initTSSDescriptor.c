#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void initializeTSS() {
	Descriptor* target = &gdt[INDEX_TSS];	
	memset(&tss, 0, sizeof(tss));
	u32 base = (u32)gdt[INDEX_FLAT_RW].baseLow;
	base = base | (gdt[INDEX_FLAT_RW].basehigh1 << 16);
	base = base | (gdt[INDEX_FLAT_RW].baseHigh2 << 24);
	base += (u32)&tss;
	u32 limit = sizeof(tss) - 1;
	u16 attribute = DA_32 | DA_P | DA_NS | DA_386TSS;
	initializeDescriptor(target, base, limit, attribute);
	newDescIndex++;
}