#kernel location
ENTRYPOINT	=	0x30400

ASM			=	nasm
LD			=	ld
CC			=	gcc
ASMBFLAGS	=	-I booter/include/
ASMKFLAGS	=	-f elf32
CFLAGS		=	-m32 -c -I kernel/include
LDFLAGS		=	-m elf_i386 -s -Ttext ${ENTRYPOINT}

#TARGET
BOOTER		=	booter/bootSector.bin booter/Loader.bin
KERNEL		=	kernel/Kernel.bin
OBJS		=	kernel/Kernel.o kernel/start.o kernel/global.o kernel/initialize8259A.o kernel/initializeIDT.o\ 
				kernel/lib/string.o	kernel/lib/operatePort.o kernel/lib/interruptHandler.o kernel/lib/exceptionHandler.o\
				kernel/lib/displayInt.o

.PHONY		:	all everything cleanAllBin cleanAllO buildImg

all			:	cleanAllBin everything cleanAllO
everything	:	${BOOTER} ${KERNEL}
cleanAllBin	:
				rm -f ${BOOTER} ${KERNEL}
cleanAllO	:	
				rm -f ${OBJS}
buildImg	:	
				dd if=/dev/zero of=../a.img bs=512 count=2880
				dd if=booter/bootSector.bin of=../a.img bs=512 count=1 conv=notrunc
				mount -o loop ../a.img /mnt/floopy
				cp booter/Loader.bin /mnt/floopy
				umount /mnt/floppy

booter/bootSector.bin			:	booter/bootSector.asm  booter/include/LoadingAddress.inc booter/include/FAT12header.inc booter/include/RealModeLib.inc
									${ASM} ${ASMBFLAGS}	-o $@ $<
booter/Loader.bin				:	booter/Loader.asm booter/include/LoadingAddress.inc	booter/include/FAT12header.inc booter/include/ProtectMode.inc booter/include/RealModeLib.inc
									${ASM}	${ASMBFLAGS} -o $@ $<
kernel/Kernel.bin				:	${OBJS}
									${LD} ${LDFLAGS} -o Kernel.bin ${OBJS}


kernel/Kernel.o					:	kernel/Kernel.asm 
									${ASM} ${ASMKFLAGS} -o $@ $<

kernel/start.o					:	kernel/start.c kernel/include/type.h kernel/include/const.h kernel/include/important.h kernel/include/global.h kernel/include/prototype.h
									${CC} ${CFLAGS} -o $@ $<

kernel/lib/string.o				:	kernel/lib/string.asm
									${ASM} ${ASMKFLAGS} -o $@ $<

kernel/lib/operatePort.o		:	kernel/lib/operatePort.asm 
									${ASM} ${ASMKFLAGS} -o $@ $<

kernel/lib/interruptHandler.o   :	kernel/lib/interruptHandler.asm
									${ASM} ${ASMKFLAGS} -o $@ $<

kernel/global.o					:	kernel/global.c  kernel/include/global.h
									${CC} ${CFLAGS} -o $@ $<

kernel/initialize8259A.o		:	kernel/initialize8259A.c kernel/include/type.h kernel/include/const.h kernel/include/prototype.h
									${CC} ${CFLAGS} -o $@ $<

kernel/initializeIDT.o			:	kernel/initializeIDT.c kernel/include/type.h kernel/include/global.h kernel/include/intVector.h kernel/include/prototype.h
									${CC} ${CFLAGS} -o $@ $<

kernel/lib/dispInt.o			:	kernel/lib/dispInt.c kernel/include/type.h kernel/include/prototype.h
									${CC} ${CFLAGS} -o $@ $<

kernel/lib/exceptionHandler.o	:	kernel/lib/exceptionHandler.c kernel/include/type.h kernel/include/global.h kernel/include/prototype.h
									${CC} ${CFLAGS} -o $@ $<
