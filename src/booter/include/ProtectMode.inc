;DA= descriptor attribute
MACRO_DA_32				equ			0x4000		;D/B
MACRO_DA_4K				equ			0x8000		;G

MACRO_DA_P				equ			0x80		;P
MACRO_DA_NP				equ			0x00		;NP=no presence

MACRO_DA_S				equ			0x10		;S
MACRO_DA_NS				equ			0x00		;NS=not system

MACRO_DA_DPL0			equ			0x00		;DPL=descriptor privilege
MACRO_DA_DPL1			equ			0x20
MACRO_DA_DPL2			equ			0x40
MACRO_DA_DPL3			equ			0x60

;Data Type
MACRO_DA_D_0			equ			0x00		; data read-only
MACRO_DA_D_E			equ			0x04		; data extensible
MACRO_DA_D_W			equ			0x02		; data writable
MACRO_DA_D_A			equ			0x01		; data accessed

;Segment Type
MACRO_DA_C_X			equ			0x08		; code executable
MACRO_DA_C_C			equ			0x04		; code comforming
MACRO_DA_C_R			equ			0x02		; code readable
MACRO_DA_C_A			equ			0x01		; code accessed 


;SA=selector attribute
MACRO_SA_RPL0			equ			0
MACRO_SA_RPL1			equ			1
MACRO_SA_RPL2			equ			2
MACRO_SA_RPL3			equ			3

MACRO_SA_TIG			equ			0			;global descriptor
MACRO_SA_TIL			equ			4			;local  descriptor

;PDE Attribute
MACRO_PDE_NP			equ			0
MACRO_PDE_P				equ			1
MACRO_PDE_R				equ			0			;page read-only
MACRO_PDE_RW			equ			2			;page readrable and writable
MACRO_PDE_U				equ			0			;user page
MACRO_PDE_S				equ			4			;supervisor privilege level
MACRO_PDE_PWB			equ			0			;page cache with write-back algorithm
MACRO_PDE_PWT			equ			8			;page cache with write-through algorithm
MACRO_PDE_PCA			equ			0			;page cache abled
MACRO_PDE_PCD			equ			16			;page cache disabled
MACRO_PDE_NA			equ			0			;page not accessed
MACRO_PDE_A				equ			32			;page accessed
MACRO_PDE_PS			equ			0			;page size:0 indicates 4K Bytes
MACRO_PDE_L				equ			0			;local page
MACRO_PDE_G				equ			256			;Global page 

;PTE Attribute
MACRO_PTE_NP			equ			0
MACRO_PTE_P				equ			1
MACRO_PTE_R				equ			0			;page read-only
MACRO_PTE_RW			equ			2			;page readrable and writable
MACRO_PTE_U				equ			0			;user page
MACRO_PTE_S				equ			4			;supervisor privilege level
MACRO_PTE_PWB			equ			0			;page cache with write-back algorithm
MACRO_PTE_PWT			equ			8			;page cache with write-through algorithm
MACRO_PTE_PCA			equ			0			;page cache abled
MACRO_PTE_PCD			equ			16			;page cache disabled
MACRO_PTE_NA			equ			0			;page not accessed
MACRO_PTE_A				equ			32			;page accessed
MACRO_PTE_C				equ			0			;not be wrote yet
MACRO_PTE_D				equ			64			;have been written
MACRO_PTE_L				equ			0			;local page
MACRO_PTE_G				equ			256			;Global page 






;descriptor macro
%macro Descriptor 3
	dw		%2	&	0x0ffff
	dw		%1	&	0x0ffff
	db		(%1 >> 16) &0x0ff
	dw		((%2 >> 8) & 0x0f00) | (%3 & 0xf0ff)
	db		(%1 >> 24) & 0xff
%endmacro

