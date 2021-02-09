LABEL_SelectorFlatC		equ		8

extern	cstart		;function
extern	gdtPos		;variable
extern	idtPos		
extern	dispPos
extern	a
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
	jmp LABEL_SelectorFlatC:csinit
csinit:
    int 0x01
	jmp $
	sti
	ud2	
	push 0
	popfd
	hlt