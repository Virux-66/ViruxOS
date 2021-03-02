#include "type.h"
#include "port.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "task.h"
#include "global.h"

PUBLIC void initializeLDT() {
	Descriptor* target = &gdt[INDEX_LDT_FIRST];
	PCB* pointer = PCBTable;
	for (int i = 0; i < processNumber; i++) {
		u32 base = (u32)gdt[INDEX_FLAT_RW].baseLow;
		base = base | (gdt[INDEX_FLAT_RW].basehigh1 << 16);
		base = base | (gdt[INDEX_FLAT_RW].baseHigh2 << 24);
		base += (u32)&(pointer->ldt);
		u32 limit = sizeof(pointer->ldt) - 1;
		u16 attribute = DA_32 | DA_P | DA_NS | DA_LDT;
		initializeDescriptor(target, base, limit, attribute);
		target++;
		pointer++;
		newDescIndex++;
	}
}