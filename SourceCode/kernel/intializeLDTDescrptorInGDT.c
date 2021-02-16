#include "type.h"
#include "global.h"
#include "important.h"
#include "process.h"
#include "prototype.h"

PUBLIC void intializeLDT() {
	Descriptor* target = &gdt[INDEX_LDT_FIRST];
	PCB* pointer = PCBTable;
	for (int i = 0; i < processNumber; i++) {
		u32 base = (u32)gdt[INDEX_FLAT_RW].baseLow;
		base = base | (gdt[INDEX_FLAT_RW].basehigh1 << 16);
		base = base | (gdt[INDEX_FLAT_RW].baseHigh2 << 24);
		base += &(pointer->ldt);
		u32 limit = sizeof(pointer->ldt) - 1;
		u16 attribute = DA_32 | DA_P | DA_NS | DA_LDT;
		intializeDescriptor(target, base, limit, attribute);
		target++;
		pointer++;
	}
}