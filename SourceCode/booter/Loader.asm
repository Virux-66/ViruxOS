org 0x100
MACRO_STACK_BASE		equ			0x9000
MACRO_STACK_OFFSET		equ			0x100


	jmp LABEL_CODE_ENTRY
%include 	"LoadingAddress.inc"
%include	"FAT12header.inc"
%include	"ProtectMode.inc"

;;;;;;Global Descriptor Table
LABEL_GDT:				Descriptor			0,				0,				0
LABEL_DESC_FLAT_C:		Descriptor			0,			0xfffff,	MACRO_DA_32|MACRO_DA_4K|MACRO_DA_C_X|MACRO_DA_C_R|MACRO_DA_P|MACRO_DA_S
LABEL_DESC_FLAT_RW:		Descriptor			0,			0xfffff,	MACRO_DA_32|MACRO_DA_4K|MACRO_DA_D_W|MACRO_DA_P|MACRO_DA_S
LABEL_DESC_VIDEO:		Descriptor		0xb8000,		0xffff,		MACRO_DA_D_W|MACRO_DA_DPL3|MACRO_DA_P|MACRO_DA_S
MACRO_GDTLEN			equ			$-LABEL_GDT
LABEL_GDTPOS:			dw			MACRO_GDTLEN-1
						dd			MACRO_LOADER_BASE*0x10+LABEL_GDT

;;;;;;;Selector
LABEL_SelectorFlatC			equ			LABEL_DESC_FLAT_C-LABEL_GDT
LABEL_SelectorFlatRW		equ			LABEL_DESC_FLAT_RW-LABEL_GDT
LABEL_SelectorVideo			equ			LABEL_DESC_VIDEO-LABEL_GDT



LABEL_CODE_ENTRY:
	mov ax,cs
	mov ds,ax
	mov es,ax
	mov ax,MACRO_STACK_BASE
	mov ss,ax
	mov sp,MACRO_STACK_OFFSET
	
	mov ax,0x01
	mov dx,0x0000
	call @DispStr
	mov ax,0x02
	mov dx,0x0100
	call @DispStr

LABEL_CODE_FLOOPYDRIVER_RESET:
	xor ah,ah
	xor dl,dl
	int 0x13
	
LABEL_CODE_LOADING_KERNEL:
	mov ax,0x03
	mov dx,0x0200
	call @DispStr
	mov byte dl,[LABEL_DATA_ROOTDIRECTORY_SIZE]
	mov ax,MACRO_KERNEL_BASE
	mov es,ax
	mov bx,MACRO_KERNEL_OFFSET
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
	jmp LABEL_CODE_READING_KERNEL
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
	mov al,0x04
	mov dx,0x0300
	call @DispStr

	jmp $

LABEL_CODE_READING_KERNEL:
	xor ax,ax
	mov al,0x05
	mov dx,0x0400
	call @DispStr
	sub di,0x0b	
	mov word ax,[es:di+0x1a]					
	mov word bx,[es:di+0x1c]
	mov word [LABEL_DATA_KERNELBIN_SIZE],bx
	mov word bx,[es:di+0x1e]
	mov word [LABEL_DATA_KERNELBIN_SIZE+0x02],bx	
	mov bx,MACRO_KERNEL_OFFSET				      ;es:bx=0x8000:0x00
	mov cx,0x01
 .LABEL_CODE_READING_KERNEL_ACCORDINGTO_CLUSTER:
	push ax
	add ax,MACRO_SECTOR_DELAT
	add ax,MACRO_ROOTDIRECTORY_SIZE
	call @ReadSection
	pop ax
	call @GetNextCluster
	add bx,0x200
	cmp ax,0x0fff
	jnz .LABEL_CODE_READING_KERNEL_ACCORDINGTO_CLUSTER	
LABEL_CODE_JUMP_TO_KERNEL_PM:
	call @KillMotor
	xor ax,ax
	mov al,0x06
	mov dx,0x0500
	call @DispStr
	mov ax,0x07
	mov dx,0x0600
	call @DispStr
	
; call int 15h
LABEL_CODE_MEMCHK:
	mov ax,cs
	mov es,ax
	mov di,LABEL_REAL_ARDS_BUF
	mov ebx,0x00
	mov edx,0x0534D4150
 .MEMCHK_LOOP:
	mov eax,0x0E820
	mov ecx,20
	int 0x15
	jc .MEMCHK_FAIL
	inc dword [LABEL_REAL_MCKNUM]
	cmp ebx,0x00
	jz .MEMCHK_COMPLETE
	add di,20
	jmp .MEMCHK_LOOP
 .MEMCHK_FAIL:
	mov dword [LABEL_REAL_MCKNUM],0x00
 .MEMCHK_COMPLETE:

LABEL_CODE_SET_MCKSIZE:				;0x9000:0x0262
	mov di,LABEL_REAL_ARDS_BUF
	mov dword ecx,[LABEL_REAL_MCKNUM]
 .LOOP:
	mov dword eax,[es:di+0x10]
	cmp eax,0x01
	jnz	.GO_ON
	mov dword eax,[es:di]
	add dword eax,[es:(di+8)]
	cmp eax,[LABEL_REAL_MEMSIZE]
	jb .GO_ON
	mov [LABEL_REAL_MEMSIZE],eax
 .GO_ON:
	add di,20
	loop .LOOP
	

;;;;;;into protect mode

	;1: load gdt
	lgdt [LABEL_GDTPOS]

	;2:	
	cli

	;3:	open A20
	in al,0x92
	or al,0000_0010b
	out 0x92,al

	;4:set cr0
	mov eax,cr0
	or eax,1
	mov cr0,eax

	;5:jump into protect mode  ;0x9000:0x02a4
	jmp	dword	LABEL_SelectorFlatC:(MACRO_LOADER_BASE*0x10+LABEL_CODE_PMSTART)
	
	%include "RealModeLib.inc"  ;if put behind [SECTION s32] , it will be compiled to 32-bit mode

LABEL_DATA_AREA:
	LABEL_DATA_KERNELBIN_SIZE:			dd				0
	LABEL_DATA_ROOTDIRECTORY_SIZE:		db		MACRO_ROOTDIRECTORY_SIZE
	LABEL_DATA_ROOTDIRECTORY_NO:		db		MACRO_ROOTDIRECTORY_OFFSET
	LABEL_DATA_FILENAME:				db		'KERNEL  BIN'

	MACRO_DATA_MESSAGE_LENGTH			equ				42
	LABEL_DATA_MESSAGE_START:			db			'                                          '
	LABEL_DATA_MESSAGE_1:				db			'Executing in loader!                      '
	LABEL_DATA_MESSAGE_2:				db			'Executing in 16-bit Mode!                 '
	LABEL_DATA_MESSAGE_3:				db			'Finding kernel right now!                 '
	LABEL_DATA_MESSAGE_4:				db			'Kernel dose not exist!                    '
	LABEL_DATA_MESSAGE_5:				db			'Loading kernel into memory!               '
	LABEL_DATA_MESSAGE_6:				db			'Be ready to jump to 32-bit protected Mode!'
	LABEL_DATA_MESSAGE_7:				db			'Calling int 0x15 to check memory!         '
	
	;9000:0247


	

[SECTION s32]
[BITS 32]
LABEL_CODE_PMSTART:
	;0x0008:0x0009038c

	mov ax,LABEL_SelectorFlatRW
	mov ds,ax
	mov es,ax
	;mov gs,ax
	mov fs,ax
	mov ss,ax
	mov sp,MACRO_TOPOFSTACK
	mov ax,LABEL_SelectorVideo
	mov gs,ax
	mov ah,0x0f
	mov al,'!'
	mov [gs:((80*0+39)*2)],ax









	call @SetupPaging

	call @InitKernel


	jmp LABEL_SelectorFlatC:MACRO_KERNEL_RELOADING
MACRO_s32_LEN			equ				$-LABEL_CODE_PMSTART



@SetupPaging:
	xor eax,eax
	xor edx,edx
	mov eax,[MACRO_PM_MEMSIZE]
	mov ebx,0x400000
	div ebx
	test edx,0
	jz .No_reminder1
	inc eax
 .No_reminder1:
	mov ecx,eax
	mov ax,LABEL_SelectorFlatRW
	mov es, ax
	xor eax,eax
	mov edi,MACRO_PAGEDIRECTORYTABLE_BASE
	mov eax,MACRO_PDE_P | MACRO_PDE_RW | MACRO_PDE_S | MACRO_PAGETABLE_BASE
 .LOOP1:
	stosd				;after then edi will be increased by four
	mov eax,4096		;page table base 4K-alignment
	loop .LOOP1

	xor eax,eax
	xor edx,edx
	mov eax,[MACRO_PM_MEMSIZE]
	mov ebx,0x1000
	div ebx
	test edx,0
	jz .No_reminder2
	inc eax
 .No_reminder2:
	mov ecx,eax
	xor eax,eax
	mov edi , MACRO_PAGETABLE_BASE
	mov eax , MACRO_PTE_P | MACRO_PTE_RW | MACRO_PTE_S
 .LOOP2:
	stosd
	mov eax,4096
	loop .LOOP2

	xor eax,eax
	mov eax , MACRO_PAGEDIRECTORYTABLE_BASE
	mov cr3,eax
	mov eax,cr0
	or eax,	0x80000000
	mov cr3,eax
	;jmp short .3
	; 3.:
	nop
	ret


@InitKernel:
	push eax
	push ebx
	push ecx
	push esi


	mov ebx,MACRO_KERNEL_BASE*0x10
	mov word cx,[ebx+0x2c]						;program header number
	movzx ecx,cx
	mov eax,[ebx+0x1c]
	add eax,MACRO_KERNEL_BASE*0x10			;program header table address
	mov esi,eax
 .LOOP:
	mov eax,[esi]		;0x0008:0x090455
	cmp eax,0x01
	jnz .NEXTPH
	mov eax,[esi+0x10]			;file size
	push eax
	mov eax,[esi+0x04]			;offset
	add eax,MACRO_KERNEL_BASE*0x10
	push eax
	mov eax,[esi+0x08]			;vitual address
	push eax
	call @MemCpy
	add sp,0x0c
 .NEXTPH:
	add esi,0x20
	loop .LOOP
 .RET:
	pop esi
	pop ecx
	pop ebx
	pop eax
	ret

@MemCpy:				;pass parameters by stack
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






[SECTION .DATA]
[BITS 32]
LABEL_DATA32:
	LABEL_REAL_MCKNUM:			dd			0
	LABEL_REAL_MEMSIZE:			dd			0
	LABEL_REAL_ARDS:
		LABEL_REAL_LOW_BASE:		dd			0
		LABEL_REAL_HIGH_BASE:		dd			0
		LABEL_REAL_LOW_LEN:			dd			0
		LABEL_REAL_HIGH_LEN:		dd			0
		LABEL_REAL_TYPE:			dd			0
	LABEL_REAL_ARDS_BUF:			times 256	db		0

	MACRO_PM_MKNUM				equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_MCKNUM
	MACRO_PM_MEMSIZE			equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_MEMSIZE
	MACRO_PM_ARDS				equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_ARDS
		MACRO_PM_LOW_BASE		equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_LOW_BASE
		MACRO_PM_HIGH_BASE		equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_HIGH_BASE
		MACRO_PM_LOW_LEN		equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_LOW_LEN
		MACRO_PM_HIGH_LEN		equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_HIGH_LEN
		MACRO_PM_TYPE			equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_TYPE
	MACRO_PM_ARDS_BUF			equ			(MACRO_LOADER_BASE * 0x10)+LABEL_REAL_ARDS_BUF



MACRO_DATA32_LEN			equ				$-LABEL_DATA32

[SECTION .STACK]
[BITS 32]
LABEL_STACK32:			times	1024	db		0
MACRO_TOPOFSTACK		equ		(MACRO_LOADER_BASE * 0x10)+$
MACRO_STACK32_LEN		equ			$-LABEL_STACK32