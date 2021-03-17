#ifndef _PROTOTYPE_H
#define _PROTOTYPE_H

#include "type.h"
#include "tty.h"
#include "important.h"
#include "console.h"
//string.asm
PUBLIC void* memcpy(void* dest, void* source, int size); 

PUBLIC void  memset(void* dest, char ch, int size);
//display.asm
PUBLIC void dispStr(char* str);

PUBLIC void dispColorStr(char* str, int textColor);

PUBLIC void clear();

PUBLIC void dispInt(int num);//dispInt.c

PUBLIC void dispCR();

PUBLIC void generalExceptionHandler(int vector, int errorCode, int eip, int cs, int eflags);//exceptionHandler.c

PUBLIC void initialize8259A();//initializeA.c

PUBLIC void initializeIDT();//initilizeIDT.c

PUBLIC void initializeDescriptor(Descriptor* pointer, u32 base, u32 limit, u16 attribute);//initializeDescriptor.c
//operatePort.asm

PUBLIC u8 readPort(u16 port);

PUBLIC void disableIrq(int irq);

PUBLIC void enableIrq(int irq);

PUBLIC void writePort(u16 port, u8 value);

PUBLIC void initializePCB();//initializePCB.c

PUBLIC void initializeTSS();//initializeTSSDescriptorInGDT.c

PUBLIC void initializeLDT();//initializeLDTDescriptorInGDT.c

PUBLIC void initClock();//initClock.c

PUBLIC void initKeyboard();//initKeyboard.c

PUBLIC void TestA();//processDemo.c

PUBLIC void TestB();//processDemo.c

PUBLIC void TestC();

PUBLIC void tty();//tty.c

PUBLIC void keyProcess(TTY* pTty,u32 key);

PUBLIC void disableInt();

PUBLIC void enableInt();



//interrupt handler

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

PUBLIC void sys_call();
//interrupt service
PUBLIC void clockService(int irq);	//clockService.c

PUBLIC void keyboardService(int irq);	//keyboardService.c

PUBLIC void keyboardResolution(TTY* pTty);


PUBLIC void spurious_irq(int irq);	//init8259A.c

PUBLIC void setled();//initKeyboard.c

//syscall
PUBLIC int getTicks();
PUBLIC int getTicksService();


PUBLIC void delayInMilli();//lib/delay.c

PUBLIC void pcbSchedule();//pcbSchedule.c

//console.c
PUBLIC int isCurrentConsole(CONSOLE* pConsole); 

PUBLIC void putChar(CONSOLE* pConsole, char ch);

PUBLIC void initConsole(TTY* pTty);

PUBLIC void switchOverConsole(int consoleIndex);

PUBLIC void scrollScreen(CONSOLE* pConsole, int direction);
#endif // !_PROTOTYPE_H
