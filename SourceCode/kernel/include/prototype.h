#ifndef _PROTOTYPE_H
#define _PROTOTYPE_H

PUBLIC void* memcpy(void* dest, void* source, int size); //string.asm
PUBLIC void dispStr(char* str);//string.asm
PUBLIC void dispColorStr(char* str, int textColor);//string.asm
PUBLIC void dispInt(int num);//displayInt.c
PUBLIC void generalExceptionHandler(int vector, int errorCode, int eip, int cs, int eflags);//exceptionHandler.c
PUBLIC void initialize8259A();//initializeA.c
PUBLIC void initializeIDT();//initilizeIDT.c
PUBLIC u8 readPort(u16 port);//operatePort.asm
PUBLIC void writePort(u16 port, u8 value);//operatePort.asm



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

#endif // !_PROtOTYPE_H
