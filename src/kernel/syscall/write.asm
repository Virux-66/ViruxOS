%include "const.inc"

_NR_write		equ		1

global write

[SECTION .text]
write:
;int write(char* ,int);
	mov eax,_NR_write
;	mov ebx, null
	mov ecx,[esp+4]	;char*
	mov edx,[esp+8]	;int
	int 0x90
	ret