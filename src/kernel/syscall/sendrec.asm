%include "const.inc"

_NR_sendrec		equ		3

global sendrec
;;int sendrec(int function,int src_dest,MESSAGE* pMessage);
[SECTION .text]
sendrec:
	mov eax,_NR_sendrec
	mov ebx,[esp+4]
	mov ecx,[esp+8]
	mov edx,[esp+12]
	int 0x90
	ret