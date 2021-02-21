#ifdef _GLOBAL_VARIABLE
#undef EXTERN
#define EXTERN
#endif

EXTERN int dispPos;

EXTERN int newDescIndex;//in gdt

EXTERN int intReEnterFlag;//if intReenterFlag>=0, more than one interrupts happened

EXTERN u8 gdtPos[6];//0xff 0x03 0x20 0x28 0x03 0x00

EXTERN Descriptor gdt[GDTSIZE];//this array is stored in 0x08:0x33820

EXTERN u8 idtPos[6];

EXTERN Gate idt[IDTSIZE];//this array is stored in 0x00032c40

EXTERN TSS tss;			//TSS defined in important.h

EXTERN PCB PCBTable[processNumber];

EXTERN PCB* PCBready; //PCBready is in 0x08:0x344a0, which contains 0x3c4c0

EXTERN u8 processStack[processStackSize*processNumber]; //0x344c4

EXTERN TASK taskTable[taskNumber];

EXTERN irqService irqServiceTable[16];		//save irq service function pointer
