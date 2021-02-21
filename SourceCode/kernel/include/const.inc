MACRO_Selector_Dummy	equ			0x00
MACRO_SelectorFlatC		equ			0x08
MACRO_SelectorFlatRW	equ			0x10
MACRO_SelectorVideo		equ			0x18
MACRO_SelectorTSS		equ			0x20
MACRO_SelectorLDT		equ			0x28
;;use these macro with esp pointing to PCB start to locate members in PCB
MACRO_P_PCBStart			equ			0x00
MACRO_P_GSREG				equ			0x00
MACRO_P_FSREG				equ			0x04
MACRO_P_ESREG				equ			0x08
MACRO_P_DSREG				equ			0x0c
MACRO_P_EDIREG				equ			0x10
MACRO_P_ESIREG				equ			0x14
MACRO_P_EBPREG				equ			0x18
MACRO_P_KESPREG				equ			0x1c
MACRO_P_EBXREG				equ			0x20
MACRO_P_ECXREG				equ			0x24
MACRO_P_EDXREG				equ			0x28
MACRO_P_EAXREG				equ			0x2c
MACRO_P_RETADDR				equ			0x30
MACRO_P_EIPREG				equ			0x34
MACRO_P_CSREG				equ			0x38
MACRO_P_EFLAGSREG			equ			0x3c
MACRO_P_ESPREG				equ			0x40
MACRO_P_SSREG				equ			0x44
MACRO_P_STACKTOP			equ			0x48
MACRO_P_PCBSel				equ			0x48
MACRO_P_PCBLDT				equ			0x4a
;TSS index
MACRO_T_BACKLINK			equ			0x00
MACRO_T_ESP0				equ			0x04
MACRO_T_SS0					equ			0x08
MACRO_T_ESP1				equ			0x0c
MACRO_T_SS1					equ			0x10
MACRO_T_ESP2				equ			0x14
MACRO_T_SS2					equ			0x18
MACRO_T_CR3					equ			0x1c
MACRO_T_EIP					equ			0x20
MACRO_T_FLAGS				equ			0x24
MACRO_T_EAX					equ			0x28
MACRO_T_ECX					equ			0x2c
MACRO_T_EDX					equ			0x30
MACRO_T_EBX					equ			0x34
MACRO_T_ESP					equ			0x38
MACRO_T_EBP					equ			0x3c
MACRO_T_ESI					equ			0x40
MACRO_T_EDI					equ			0x44
MACRO_T_ES					equ			0x48
MACRO_T_CS					equ			0x4c
MACRO_T_SS					equ			0x50
MACRO_T_DS					equ			0x54
MACRO_T_FS					equ			0x58
MACRO_T_GS					equ			0x5c
MACRO_T_LDT					equ			0x60
MACRO_T_TRAP				equ			0x64
MACRO_T_IOBASE				equ			0x66



;;8259A port number
INT_8259A_MASTER_PORT1	equ			0x20
INT_8259A_MASTER_PORT2	equ			0x21
INT_8259A_SLAVE_PORT1	equ			0xa0	
INT_8259A_SLAVE_PORT2	equ			0xa1

EOI						equ			0x20