#ifndef _PROTOTYPE_H
#define _PROTOTYPE_H

PUBLIC void* memcpy(void* dest, void* source, int size); //string.asm
PUBLIC void  memset(void* dest, char ch, int size);
PUBLIC void dispStr(char* str);//string.asm
PUBLIC void dispColorStr(char* str, int textColor);//string.asm
PUBLIC void dispInt(int num);//dispInt.c
PUBLIC void generalExceptionHandler(int vector, int errorCode, int eip, int cs, int eflags);//exceptionHandler.c
PUBLIC void initialize8259A();//initializeA.c
PUBLIC void initializeIDT();//initilizeIDT.c
PUBLIC void initializeDescriptor(Descriptor* pointer, u32 base, u32 limit, u16 attribute);//initializeDescriptor.c
PUBLIC u8 readPort(u16 port);//operatePort.asm
PUBLIC void writePort(u16 port, u8 value);//operatePort.asm
PUBLIC void initializePCB();//initializePCB.c
PUBLIC void initializeTSS();//initializeTSSDescriptorInGDT.c
PUBLIC void initializeLDT();//initializeLDTDescriptorInGDT.c
PUBLIC void TestA();//processDemo.c
PUBLIC void TestB();//processDemo.c


//the following is interrup handler
PUBLIC void divideErrorHandler();
PUBLIC void debugExceptionHandler();
PUBLIC void nmiHandler();
PUBLIC void breakPointerHandler();
PUBLIC void overFlowHandler();
PUBLIC void boundsCheckHandler();
PUBLIC void undefinedHandler();
PUBLIC void deviceUselessHandler();
PUBLIC void doubleFaultHandler();
PUBLIC void segmentOverHandler();
PUBLIC void invalidTSSHandler();
PUBLIC void segmentNotpresentHandler();
PUBLIC void stackErrorHandler();
PUBLIC void generalProtectionHandler();
PUBLIC void pageFaultHandler();
PUBLIC void floatMistakeHandler();
PUBLIC void IRQ0Handler();
PUBLIC void IRQ1Handler();
PUBLIC void IRQ2Handler();
PUBLIC void IRQ3Handler();
PUBLIC void IRQ4Handler();
PUBLIC void IRQ5Handler();
PUBLIC void IRQ6Handler();
PUBLIC void IRQ7Handler();
PUBLIC void IRQ8Handler();
PUBLIC void IRQ9Handler();
PUBLIC void IRQ10Handler();
PUBLIC void IRQ11Handler();
PUBLIC void IRQ12Handler();
PUBLIC void IRQ13Handler();
PUBLIC void IRQ14Handler();
PUBLIC void IRQ15Handler();
#endif // !_PROtOTYPE_H
