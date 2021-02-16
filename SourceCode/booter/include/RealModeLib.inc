@ReadSection:            ;argument: es:bx buffer   cl:how many section to read     ax: starting point
	push ax
	push cx
	push dx
	
	mov dh,[BPB_SecPerTrk]
	div dh
	mov ch,al
	shr ch,1			;cylinder number		
	mov dh,al
	and dh,0x01			;header number
	mov dl,[BS_DrvNum]	;driver number
	mov al,ah
	inc al				;section number
	mov ah,cl			;how many number to read
	mov cl,al			;section number
	mov al,ah			;how many number to read
 .TRY_AGAIN:
	mov ah,0x02
	int 0x13
	jc .TRY_AGAIN

	pop dx
	pop cx
	pop ax
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@DispStr:				;al offset of string based on START   ah=0
	push ax 
	push bx
	push cx
	push dx
	push es
	push bp

	xor cx,cx
	mov cx,MACRO_DATA_MESSAGE_LENGTH		;string length
	mul cx
	add ax,LABEL_DATA_MESSAGE_START
	mov bp,ax								;string offset
	mov ax,cs
	mov es,ax								;string base
	mov dx,0x00								;disp pointer
	mov bx,0x0007							;property
	mov ax,0x1301							
	int 0x10

	pop bp
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@GetNextCluster:					;argument: ax  result: ax
	push bx
	push cx
	push dx
	push bp
	push es

	xor dx,dx
	mov bx,3
	mul bx
	mov bx,2
	div bx
	mov bp,sp
	sub sp,0x02
	mov [ss:bp-0x02],dx             ;decide how to get FAT item
	mov bx,512
	xor dx,dx
	div bx							; dx is the offset based on section where the byte is 
	inc ax
	push ax
	mov ax,0x7e00
	mov es,ax
	pop ax
	xor bx,bx
	mov cl,2
	call @ReadSection
	mov bx,dx
	mov word ax,[es:bx]
	mov dx,[ss:bp-0x02]
	mov sp,bp
	cmp dx,0x00
	jz .EVEN
 .ODD:
	shr ax,4
	jmp .RET
 .EVEN:
	and ax,0x0fff
 .RET:
	pop es
	pop bp
	pop dx
	pop cx
	pop bx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@KillMotor:
	push dx
	mov dx,0x3f2
	mov al,0
	out dx,al
	pop dx
	ret
