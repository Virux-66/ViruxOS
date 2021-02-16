global readPort
global writePort

;PUBLIC int readPort(u16 port);
readPort:
	push ebp
	mov ebp,esp
	push edx
	mov edx,[ebp+0x08]
	in al,dx
	nop
	nop
	pop edx
	pop ebp
	ret
;PUBLIC void writePort(u16 port,u8 value);
writePort:
	push ebp
	mov ebp,esp
	push eax
	push edx
	mov edx,[ebp+0x08]
	mov eax,[ebp+0x0c]
	out	dx,al
	nop				;read or write has kind of delay
	nop
	pop edx
	pop eax
	pop ebp
	ret