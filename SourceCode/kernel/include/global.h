#ifdef _GLOBAL_VARIABLE
#undef EXTERN
#define EXTERN
#endif

EXTERN int dispPos;

EXTERN int newDescIndex;//in gdt

EXTERN int intReEnterFlag;//first initialized in Kernel.asm

EXTERN int ticks;

EXTERN u8 gdtPos[6];//0xff 0x03 0x20 0x28 0x03 0x00

EXTERN Descriptor gdt[GDTSIZE];//this array is stored in 0x08:0x33820

EXTERN u8 idtPos[6];

EXTERN Gate idt[IDTSIZE];//this array is stored in 0x00032c40

EXTERN TSS tss;			//TSS defined in important.h

EXTERN PCB PCBTable[processNumber];

EXTERN PCB* PCBready; //PCBready is in 0x08:0x344a0, which contains 0x3c4c0

//EXTERN KB_INPUT kb_in;

extern u8 processStack[]; //0x344c4

extern TASK taskTable[];

extern irqService irqServiceTable[];		//save irq service function pointer

extern systemCall sysCallTable[];

extern char string1[];

extern char string2[];

extern char string3[];

extern char string4[];

extern char string5[];

extern char string6[];



EXTERN int code_with_E0;
EXTERN int shift_l ;
EXTERN int shift_r ;
EXTERN int alt_l;
EXTERN int alt_r;
EXTERN int ctrl_l;
EXTERN int ctrl_r;
EXTERN int caps_lock;
EXTERN int num_lock;
EXTERN int scroll_lock;
EXTERN int column;

