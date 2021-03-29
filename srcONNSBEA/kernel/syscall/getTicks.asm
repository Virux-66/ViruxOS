%include "const.inc"

_NR_get_ticks		equ		0

global getTicks

[SECTION .text]
;int getTicks();
getTicks:
	mov eax, _NR_get_ticks	
	int 0x90
	ret