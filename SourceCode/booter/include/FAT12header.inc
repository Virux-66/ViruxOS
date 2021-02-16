;FAT12 header infomation
;total=59 bytes
BS_OEMName:			db			'Virux   '			;manufacture name, must be 8 bytes
BPB_BytsPerSec:		dw			0x200				;how many bytes in each section
BPB_SecPerClus:		db			0x01				;how many section in each cluster
BPB_RsvdSecCnt:		dw			0x01				;how many section boot section occupies
BPB_NumFATs:		db			0x02				;how many FAT table totally
BPB_RootEntCnt:		dw			0xe0				;how many files in root directory
BPB_TotSec16:		dw			0xb40				;total section
BPB_Media:			db			0xf0
BPB_FATSz16:		dw			0x09				;how many section in each FAT
BPB_SecPerTrk:		dw			0x12				;how many section in each track
BPB_NumHeads:		dw			0x02				;header number
BPB_HiddSec:		dd			0x0					
BPB_TotSec32:		dd			0x0	
BS_DrvNum:			db			0x0			
BS_Reserved1:		db			0x0
BS_BootSig:			db			0x0
BS_VolID:			dd			0x0
BS_VolLab:			db			'Virux01    '
BS_FileSysType:		db			'FAT12   '

;self-define:
MACRO_SECTOR_DELAT			equ		17
MACRO_ROOTDIRECTORY_SIZE	equ		14			;in section
MACRO_ROOTDIRECTORY_OFFSET	equ		19