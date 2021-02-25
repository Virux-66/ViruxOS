%include "const.inc"

extern	cstart			;function
extern	gdtPos			;global variable
extern	idtPos			;global variable
extern	dispPos			;global variable
extern  PCBready		;global variable
extern	intReEnterFlag	;global variable
extern	tss				;global variable

global LABEL_TOPOFSTACK
global halt

[SECTION .bss]
LABEL_STACK_KERNEL:		resb		2*1024
LABEL_TOPOFSTACK:

[SECTION .text]
global _start

_start:
	mov esp,LABEL_TOPOFSTACK	;LABEL_TOPSTACK=0x32800  ss=0x10
	mov dword [dispPos],0x00	;label dispPos is 0x32800
	mov dword [intReEnterFlag],0x00
	sgdt [gdtPos];label gdtPos is 0x32c20
	call cstart
	lgdt [gdtPos]
	lidt [idtPos]					;label idtPos is 0x32804
	jmp MACRO_SelectorFlatC:csinit
csinit:								;0x08:0x3043a
;start the first process, recover the first process field
    mov ax,MACRO_SelectorTSS
	ltr ax
	mov esp,[PCBready]
	lldt [esp+MACRO_P_PCBSel]
	lea eax,[esp+MACRO_P_STACKTOP]
	mov dword [tss+MACRO_T_ESP0],eax

	dec dword [intReEnterFlag]
	pop gs
	pop fs
	pop es
	pop ds
	popad
	add esp,4
	;sti
	;hlt
	iretd