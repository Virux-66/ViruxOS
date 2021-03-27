%include "const.inc"

_NR_printx		equ		2

global printx

[SECTION .text]
;printx(char*)
printx:
	mov eax,_NR_printx
	mov edx,[esp+4]
	int 0x90
	ret