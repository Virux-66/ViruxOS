#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "global.h"

PRIVATE void initializeIdtDesc(unsigned char vector, u8 type,
	intHandler	handler, unsigned char privilege) {
	Gate* gate = &idt[vector];
	u32 offset = (u32)handler;
	gate->offsetLow = offset & 0xffff;
	gate->selector = 0x08;////////////////!!!!!!!
	gate->attr1 = 0x00;
	gate->attr2 = type | (privilege << 5);
	gate->offsetHigh = (offset >> 16) & 0xffff;
}

PUBLIC void initializeIDT() {
	initializeIdtDesc(INT_VECTOR_DE, DA_NS |DA_P |DA_386IGATE, divideErrorHandler, 0);
	initializeIdtDesc(INT_VECTOR_DB, DA_NS | DA_P | DA_386IGATE, debugExceptionHandler, 0);
	initializeIdtDesc(INT_VECTOR_NMI, DA_NS | DA_P | DA_386IGATE, nmiHandler, 0);
	initializeIdtDesc(INT_VECTOR_BP, DA_NS | DA_P | DA_386IGATE, breakPointerHandler, 0);
	initializeIdtDesc(INT_VECTOR_OF, DA_NS | DA_P | DA_386IGATE, overFlowHandler, 0);
	initializeIdtDesc(INT_VECTOR_BR, DA_NS | DA_P | DA_386IGATE, boundsCheckHandler, 0);
	initializeIdtDesc(INT_VECTOR_UD, DA_NS | DA_P | DA_386IGATE, undefinedHandler, 0);
	initializeIdtDesc(INT_VECTOR_NM, DA_NS | DA_P | DA_386IGATE, deviceUselessHandler, 0);
	initializeIdtDesc(INT_VECTOR_DF, DA_NS | DA_P | DA_386IGATE, doubleFaultHandler, 0);
	initializeIdtDesc(INT_VECTOR_SEG, DA_NS | DA_P | DA_386IGATE, segmentOverHandler, 0);
	initializeIdtDesc(INT_VECTOR_TS, DA_NS | DA_P | DA_386IGATE, invalidTSSHandler, 0);
	initializeIdtDesc(INT_VECTOR_NP, DA_NS | DA_P | DA_386IGATE, segmentNotpresentHandler, 0);
	initializeIdtDesc(INT_VECTOR_SS, DA_NS | DA_P | DA_386IGATE, stackErrorHandler, 0);
	initializeIdtDesc(INT_VECTOR_GP, DA_NS | DA_P | DA_386IGATE, generalProtectionHandler, 0);
	initializeIdtDesc(INT_VECTOR_PF, DA_NS | DA_P | DA_386IGATE, pageFaultHandler, 0);
	initializeIdtDesc(INT_VECTOR_MF, DA_NS | DA_P | DA_386IGATE, floatMistakeHandler, 0);
	initializeIdtDesc(MASTER_INT_NUM, DA_NS | DA_P | DA_386IGATE, IRQ0Handler, 0);
	initializeIdtDesc(MASTER_INT_NUM+1, DA_NS | DA_P | DA_386IGATE, IRQ1Handler, 0);
	initializeIdtDesc(MASTER_INT_NUM+2, DA_NS | DA_P | DA_386IGATE, IRQ2Handler, 0);
	initializeIdtDesc(MASTER_INT_NUM+3, DA_NS | DA_P | DA_386IGATE, IRQ3Handler, 0);
	initializeIdtDesc(MASTER_INT_NUM+4, DA_NS | DA_P | DA_386IGATE, IRQ4Handler, 0);
	initializeIdtDesc(MASTER_INT_NUM+5, DA_NS | DA_P | DA_386IGATE, IRQ5Handler, 0);
	initializeIdtDesc(MASTER_INT_NUM+6, DA_NS | DA_P | DA_386IGATE, IRQ6Handler, 0);
	initializeIdtDesc(MASTER_INT_NUM+7, DA_NS | DA_P | DA_386IGATE, IRQ7Handler, 0);
	initializeIdtDesc(SLAVE_INT_NUM, DA_NS | DA_P | DA_386IGATE, IRQ8Handler, 0);
	initializeIdtDesc(SLAVE_INT_NUM+1, DA_NS | DA_P | DA_386IGATE, IRQ9Handler, 0);
	initializeIdtDesc(SLAVE_INT_NUM+2, DA_NS | DA_P | DA_386IGATE, IRQ10Handler, 0);
	initializeIdtDesc(SLAVE_INT_NUM+3, DA_NS | DA_P | DA_386IGATE, IRQ11Handler, 0);
	initializeIdtDesc(SLAVE_INT_NUM+4, DA_NS | DA_P | DA_386IGATE, IRQ12Handler, 0);
	initializeIdtDesc(SLAVE_INT_NUM+5, DA_NS | DA_P | DA_386IGATE, IRQ13Handler, 0);
	initializeIdtDesc(SLAVE_INT_NUM+6, DA_NS | DA_P | DA_386IGATE, IRQ14Handler, 0);
	initializeIdtDesc(SLAVE_INT_NUM+7, DA_NS | DA_P | DA_386IGATE, IRQ15Handler, 0);
}
