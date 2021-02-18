%include "const.inc"

extern	cstart		;function
extern	gdtPos		;variable
extern	idtPos		
extern	dispPos
extern PCBready
[SECTION .bss]
LABEL_STACK_KERNEL:		resb		2*1024
LABEL_TOPOFSTACK:

[SECTION .text]
global _start

_start:
	mov esp,LABEL_TOPOFSTACK	;LABEL_TOPSTACK=0x32800  ss=0x10
	mov dword [dispPos],0x00	;label dispPos is 0x32800
	sgdt [gdtPos];label gdtPos is 0x32c20
	call cstart
	lgdt [gdtPos]
	lidt [idtPos];label idtPos is 0x32804
	jmp MACRO_SelectorFlatC:csinit
csinit:;0x08:0x30430
    mov ax,MACRO_SelectorTSS
	ltr ax
	mov esp,[PCBready]
	lldt [esp+72]
	pop gs
	pop fs
	pop es
	pop ds
	popad
	add esp,4
	iretd