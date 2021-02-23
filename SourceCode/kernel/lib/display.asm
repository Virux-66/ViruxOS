global dispStr
global dispColorStr
global clear

extern dispPos


;;PUBLIC void dispStr(char* str);
dispStr:
	push ebp
	mov ebp,esp
	push eax
	push ebx
	push esi
	push edi

	mov esi,[ss:ebp+0x08]
	mov edi,[dispPos]
	mov byte ah ,0x0f

 .1:
	lodsb 
	test al,al
	jz .RET
	cmp al,0x0a
	jnz .2
	push eax
	mov eax,edi
	mov bl,160
	div bl
	inc al
	xor ah,ah
	mul bl
	mov esi,eax
	pop eax
	jmp .1
 .2:	
	mov [gs:edi],ax
	add edi,0x02
	jmp .1

 .RET:	
	mov [dispPos],edi

	pop edi
	pop esi
	pop ebx
	pop eax
	pop ebp
	ret
;PUBLIC void dispColorStr(char* str,int textColor);
dispColorStr:
	push ebp
	mov ebp,esp
	push eax
	push ebx
	push esi
	push edi

	mov esi,[ss:ebp+0x08]
	mov edi,[dispPos]
	mov byte ah ,[ss:ebp+0x0c]

 .1:
	lodsb 
	test al,al
	jz .RET
	cmp al,0x0a
	jnz .2
	push eax
	mov eax,edi
	mov bl,160
	div bl
	inc al
	xor ah,ah
	mul bl
	mov esi,eax
	pop eax
	jmp .1
 .2:	
	mov [gs:edi],ax
	add edi,0x02
	jmp .1

 .RET:	
	mov [dispPos],edi

	pop edi
	pop esi
	pop ebx
	pop eax
	pop ebp
	ret

;void clear()
clear:
	push eax
	push ecx
	mov ecx,80*25
	mov [disPos],0x00
	mov eax,32
 .1:
	push eax
	call dispStr
	sub esp,0x04
	loop .1
	mov [dispPos],0x00
	ret