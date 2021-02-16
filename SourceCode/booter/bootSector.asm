;%define	_BOOT_DEBUG_
%ifdef	_BOOT_DEBUG_
	org 0x0100
%else
	org 0x7c00
%endif
jmp	LABEL_CODE_ENTRY
nop
%include "FAT12header.inc"
%include "LoadingAddress.inc"
%ifdef _BOOT_DEBUG_
	MACRO_STACK_BASE		equ		0x0100
%else
	MACRO_STACK_BASE		equ		0x7c00
%endif


LABEL_CODE_ENTRY:
	mov ax,cs
	mov ds,ax
	mov es,ax
	mov ax,MACRO_STACK_BASE
	mov ss,ax
	mov sp,0
LABEL_CODE_CLEAR:
	mov ax,0x0600
	mov bx,0x0700
	mov cx,0
	mov dh,0x18
	mov dl,0x4f
	int 0x10 
LABEL_CODE_FLOOPYDRIVER_RESET:
	xor ah,ah
	xor dl,dl
	int 0x13

LABEL_CODE_LOADING_LOADER:
	mov byte dl,[LABEL_DATA_ROOTDIRECTORY_SIZE]
	mov ax,MACRO_LOADER_BASE
	mov es,ax
	mov bx,MACRO_LOADER_OFFSET
	mov dh,[LABEL_DATA_ROOTDIRECTORY_NO]
 .LABEL_CODE_MAIN:
	cmp dl,0
	jz .LABEL_CODE_FAIL
	dec dl
	dec byte [LABEL_DATA_ROOTDIRECTORY_SIZE]
	push ax
	push cx
	movzx ax,dh
	mov cl,1
	call @ReadSection
	pop cx
	pop ax
	xor cx,cx
	mov cl,0x10
	mov si,LABEL_DATA_FILENAME
	mov di,bx
	mov ch,0x0b
 .LABEL_CODE_FIND_FILENAME:
	cmp cl,0
	jz .LABEL_CODE_NEXT_SECTION
	dec cl
	cld
 .LABEL_CODE_MATCHING_FILENAME:
	cmp ch,0
	jz .LABEL_CODE_FOUND
	dec ch
	lodsb
	cmp al,byte [es:di]
	jnz .LABEL_CODE_NEXT_FILENAME
	inc di
	jmp .LABEL_CODE_MATCHING_FILENAME

 .LABEL_CODE_FOUND:
	jmp LABEL_CODE_READING_LOADER
 .LABEL_CODE_NEXT_FILENAME:
	mov si,LABEL_DATA_FILENAME
	and di,0xffe0
	add di,0x20
	mov ch,0x0b
	jmp .LABEL_CODE_FIND_FILENAME
 .LABEL_CODE_NEXT_SECTION:
	inc dh
	add bx,0x200
	jmp .LABEL_CODE_MAIN
 .LABEL_CODE_FAIL:
	xor ax,ax
	mov al,0x02
	call @DispStr
%ifdef _BOOT_DEBUG_
	mov ax,0x4c00
	int 0x21
%else
	jmp $
%endif

LABEL_CODE_READING_LOADER:
	xor ax,ax
	mov al,0x01
	call @DispStr
	sub di,0x0b	
	mov word ax,[es:di+0x1a]						;starting cluster number
	mov word bx,[es:di+0x1c]
	mov word [LABEL_DATA_LOADERBIN_SIZE],bx
	mov word bx,[es:di+0x1e]
	mov word [LABEL_DATA_LOADERBIN_SIZE+0x02],bx	;file size
	mov bx,MACRO_LOADER_OFFSET						;es:bx=0x9000:0x100
	mov cx,0x01

 .LABEL_CODE_READING_LOADER_ACCORDINGTO_CLUSTER:
	push ax
	add ax,MACRO_SECTOR_DELAT
	add ax,MACRO_ROOTDIRECTORY_SIZE
	call @ReadSection 
	pop ax
	call @GetNextCluster
	add bx,0x200
	cmp ax,0x0fff 
	jnz .LABEL_CODE_READING_LOADER_ACCORDINGTO_CLUSTER	
	;; loader.bin in 0x9000:0x100
LABEL_CODE_JMP_TO_LOADER:
	jmp  MACRO_LOADER_BASE:MACRO_LOADER_OFFSET

LABEL_DATA_AREA:
	LABEL_DATA_ROOTDIRECTORY_SIZE:		db		MACRO_ROOTDIRECTORY_SIZE
	LABEL_DATA_LOADERBIN_SIZE:			dd				0
	LABEL_DATA_ROOTDIRECTORY_NO:		db		MACRO_ROOTDIRECTORY_OFFSET
	LABEL_DATA_FILENAME:				db		'LOADER  BIN'

	MACRO_DATA_MESSAGE_LENGTH			equ				9
	LABEL_DATA_MESSAGE_START:			db			'         '
	LABEL_DATA_MESSAGE_1:				db			'Ready    '
	LABEL_DATA_MESSAGE_2:				db			'NO Loader'

%include "RealModeLib.inc"

times 510-($-$$) db 0
	db	0x55,0xaa