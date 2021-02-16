#include "type.h"
#include "prototype.h"
#include "global.h"
#include "important.h"

PUBLIC void initializeTSS() {
	Descriptor* target = &gdt[INDEX_TSS];	
	memset(&tss, 0, sizeof(tss));
	u32 base = (u32)gdt[INDEX_FLAT_RW].baseLow;
	base = base | (gdt[INDEX_FLAT_RW].basehigh1 << 16);
	base = base | (gdt[INDEX_FLAT_RW].baseHigh2 << 24);
	base += &tss;
	u32 limit = sizeof(tss) - 1;
	u16 attribute = DA_32 | DA_P | DA_NS | DA_386TSS;
	intializeDescriptor(target, base, limit, attribute);
}