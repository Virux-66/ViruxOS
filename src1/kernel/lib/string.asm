global memcpy
global memset
global strlen
global strcpy

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


;;char* strcpy(char* pdest,char* psrc)
strcpy:
	push ebp
	mov ebp,esp
	mov esi,[ebp+12]
	mov edi,[ebp+8]

 .1:
	mov al,[esi]
	inc esi
	mov byte [edi],al
	inc edi

	cmp al,0
	jnz .1
	mov eax,[ebp+8]
	pop ebp
	ret


;int strlen(char* pStr);
strlen:
	push ebp
	mov ebp,esp
	mov eax,0
	mov esi,[ebp+8]
 .1:
	cmp byte [esi],0
	jz .2
	inc esi
	inc eax
	jmp .1
 .2:
	pop ebp
	ret