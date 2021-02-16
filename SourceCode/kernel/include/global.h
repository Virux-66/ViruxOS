#ifdef _GLOBAL_VARIABLE
#undef EXTERN
#define EXTERN
#endif

EXTERN int dispPos;
EXTERN u8 gdtPos[6];//0xff 0x03 0x20 0x28 0x03 0x00
EXTERN Descriptor gdt[GDTSIZE];//this array is stored in 0x00032820
EXTERN u8 idtPos[6];
EXTERN Gate idt[IDTSIZE];//this array is stored in 0x00032c40
EXTERN TSS tss;			//TSS defined in important.h
EXTERN PCB PCBTable[processNumber];
EXTERN PCB* PCBready;
EXTERN u8 processStack[processNumber][processStackSize];

