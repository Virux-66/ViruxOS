%include "const.inc"

extern	cstart			;function
extern	dispStr			;function
extern	gdtPos			;global variable
extern	idtPos			;global variable
extern	dispPos			;global variable
extern  PCBready		;global variable
extern	intReEnterFlag	;global variable
extern	tss				;global variable
extern	string1
extern	string2
extern	string3
global LABEL_TOPOFSTACK

[SECTION .bss]
LABEL_STACK_KERNEL:		resb		2*1024
LABEL_TOPOFSTACK:

[SECTION .text]
global _start

_start: ;0x08:0x30400
	mov esp,LABEL_TOPOFSTACK	
	mov dword [dispPos],1120

	push dword string1
	call dispStr
	pop eax
	mov dword [dispPos],1280
	push dword string2
	call dispStr
	pop eax
	mov dword [dispPos],1440
	push dword string3
	call dispStr
	pop eax

	mov dword [intReEnterFlag],0x00
	sgdt [gdtPos]
	call cstart
	lgdt [gdtPos]
	lidt [idtPos]					;label idtPos is 0x32804
	jmp MACRO_SelectorFlatC:csinit
csinit:								;0x08:0x3043a
;start the first process, recover the first process field
    mov ax,MACRO_SelectorTSS
	ltr ax
	mov esp,[PCBready]			;;PCBready=0x10:0x34580 PCB xp /72bx 0x10:0x445a0
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
	;int 0x21
	iretd