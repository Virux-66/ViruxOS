%include "const.inc"

_NR_exchange	equ		4

global exchange

[SECTION .text]

exchange:
;int exchange(PCKAGE* pPackage);
	mov eax,_NR_exchange
;	mov ebx,null
;	mov ecx,null
	mov edx,[esp+4]
	int 0x90
	ret