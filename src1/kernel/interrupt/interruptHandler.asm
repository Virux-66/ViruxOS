global divideErrorHandler
global debugExceptionHandler
global nmiHandler
global breakPointerHandler
global overFlowHandler
global boundsCheckHandler
global undefinedHandler
global deviceUselessHandler
global doubleFaultHandler
global segmentOverHandler
global invalidTSSHandler
global segmentNotpresentHandler
global stackErrorHandler
global generalProtectionHandler
global pageFaultHandler
global floatMistakeHandler
global IRQ0Handler
global IRQ1Handler
global IRQ2Handler
global IRQ3Handler
global IRQ4Handler
global IRQ5Handler
global IRQ6Handler
global IRQ7Handler
global IRQ8Handler
global IRQ9Handler
global IRQ10Handler
global IRQ11Handler
global IRQ12Handler
global IRQ13Handler
global IRQ14Handler
global IRQ15Handler

global sys_call

extern intReEnterFlag
extern sysCallTable

%include "const.inc"

%macro IRQMACRO		1
	call save

	in al,INT_8259A_MASTER_PORT2
	or al, (1 << %1)
	out INT_8259A_MASTER_PORT2,al						;switch off clock interrupt

	mov al,EOI
	out INT_8259A_MASTER_PORT1 , al

	sti
	;inc byte [gs:0]
	push %1														;pass parameter
	call [irqServiceTable+%1*4]									;the most important part for clock interrupt
	pop ecx
	cli

	in al,INT_8259A_MASTER_PORT2
	and al,~(1 << %1)
	out INT_8259A_MASTER_PORT2,al

	ret													;jmp to .cont or .reEntry
%endmacro
cont:		
	mov esp,[PCBready]									;
	lldt [esp+MACRO_P_PCBSel]
	lea eax,[esp+MACRO_P_STACKTOP]
	mov dword [tss+MACRO_T_ESP0],eax
reEntry:
	dec dword [intReEnterFlag]
	pop gs
	pop fs
	pop es
	pop ds
	popad
	add esp,4
	iretd








extern LABEL_TOPOFSTACK				;kernel stack esp 
extern dispStr						;extern function defined in string.asm
extern generalExceptionHandler		;extern function
extern PCBready						;global variable
extern intReEneterFlag				;global variable		;use it to decide whether to have another interrrupt
extern tss							;global varaible
extern irqServiceTable

;if the interrupt that happened has a error code, just push int vector
;otherwise,before push int vector ,push 0xffffffff
divideErrorHandler:		;0x08:0x30900
	push 0xffffffff
	push 0x00
	jmp exception
debugExceptionHandler:
	push 0xffffffff
	push 0x01
	jmp exception
nmiHandler:
	push 0xffffffff
	push 0x02
	jmp exception
breakPointerHandler:
	push 0xffffffff
	push 0x03
	jmp exception
overFlowHandler:
	push 0xffffffff
	push 0x04
	jmp exception
boundsCheckHandler:
	push 0xffffffff
	push 0x05
	jmp exception
undefinedHandler:
	push 0xffffffff
	push 0x06
	jmp exception
deviceUselessHandler:
	push 0xffffffff
	push 0x07
	jmp exception
doubleFaultHandler:
	push 0x08
	jmp exception
segmentOverHandler:
	push 0xffffffff
	push 0x09
	jmp exception
invalidTSSHandler:
	push 0x0a
	jmp exception
segmentNotpresentHandler:
	push 0x0b
	jmp exception
stackErrorHandler:
	push 0x0c
	jmp exception	
generalProtectionHandler:
	push 0x0d
	jmp exception	
pageFaultHandler:
	push 0x0e
	jmp exception	
floatMistakeHandler:
	push 0xffffffff
	push 0x10
	jmp	exception	

exception:	
	call generalExceptionHandler
	add esp,4*2
	hlt

;when entering here from process, IF = 0 and EOI=0
IRQ0Handler:
	IRQMACRO 0
IRQ1Handler:
	IRQMACRO 1
IRQ2Handler:
	IRQMACRO 2
IRQ3Handler:
	IRQMACRO 3
IRQ4Handler:
	IRQMACRO 4
IRQ5Handler:
	IRQMACRO 5
IRQ6Handler:
	IRQMACRO 6
IRQ7Handler:
	IRQMACRO 7
IRQ8Handler:
	IRQMACRO 8
IRQ9Handler:
	IRQMACRO 9
IRQ10Handler:
	IRQMACRO 10
IRQ11Handler:
	IRQMACRO 11
IRQ12Handler:
	IRQMACRO 12
IRQ13Handler:
	IRQMACRO 13
IRQ14Handler:
	IRQMACRO 14
IRQ15Handler:
	IRQMACRO 15

;edx second to last;ecx third to last;ebx the first 
sys_call:
	call save
	push dword [PCBready]
	sti
	push edx	
	push ecx	
	push ebx	
	call [sysCallTable+eax*0x04]
	add esp,16
	mov [esi+MACRO_P_EAXREG],eax
	cli
	ret

save:
	pushad
	push ds
	push es
	push fs
	push gs
	mov esi,edx
	mov dx,ss
	mov ds,dx
	mov es,dx
	mov edx,esi
	mov esi,esp
	inc dword [intReEnterFlag]
	cmp dword [intReEnterFlag],0
	jne .1
	mov esp,LABEL_TOPOFSTACK		;change esp to kernel esp
	push cont						;serve to ret
	jmp [esi+MACRO_P_RETADDR]
 .1:
	push reEntry
	jmp [esi+MACRO_P_RETADDR]