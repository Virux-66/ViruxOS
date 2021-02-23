global memcpy
global memset
;PUBLIC void* memcpy (void* dest , void* source,int size);
memcpy:				;pass parameters by stack
	push ebp
	mov ebp,esp
	push eax
	push ecx
	push esi
	push edi
	
	mov dword edi,[ebp+0x08]			
	mov dword esi,[ebp+0x0c]
	mov dword ecx,[ebp+0x10]

	cmp ecx,0x00
	jz .FINIAL
 .LOOPA:
	mov byte al,[esi]
	inc si
	mov byte [es:edi],al
	inc di
	loop .LOOPA

 .FINIAL:
	pop edi
	pop esi
	pop ecx
	pop eax
	pop ebp
	ret

;PUBLIC void memset(void* destination,char ch, int size)
memset:
	push ebp
	mov ebp,esp
	mov edi,[ss:ebp+0x08]
	mov eax,[ss:ebp+0x0c]
	mov ecx,[ss:ebp+0x10]
	cmp ecx,0x00
	jz .RET
 .loop:
	mov [edi],al
	inc edi
	loop .loop
 .RET:
	pop ebp
	ret	
