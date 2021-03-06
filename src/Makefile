#kernel location
ENTRYPOINT	=	0x30400

ASM			=	nasm
LD			=	ld
CC			=	gcc
ASMBFLAGS	=	-I booter/include/
ASMKFLAGS	=	-f elf32 -I kernel/include/
CFLAGS		=	-m32 -c -I kernel/include -std=c99 -fno-builtin
LDFLAGS		=	-m elf_i386 -s -Ttext ${ENTRYPOINT}

#TARGET
BOOTER		=	booter/bootSector.bin booter/Loader.bin
KERNEL		=	kernel/Kernel.bin
OBJS		=	kernel/Kernel.o kernel/start.o kernel/global.o kernel/processDemo.o kernel/process.o \
kernel/console.o kernel/mistake.o \
kernel/systemtask/sys_tty.o kernel/systemtask/sys_task.o\
kernel/lib/delay.o kernel/lib/dispInt.o kernel/lib/display.o kernel/lib/operatePort.o kernel/lib/string.o \
kernel/lib/openIrq.o kernel/lib/interrupt.o \
kernel/init/init8259A.o kernel/init/initDescriptor.o kernel/init/initIDT.o kernel/init/initLDTDescriptor.o \
kernel/init/initPCB.o kernel/init/initTSSDescriptor.o kernel/init/initVariable.o kernel/init/initClock.o \
kernel/init/initKeyboard.o \
kernel/interrupt/exceptionHandler.o kernel/interrupt/clockService.o kernel/interrupt/interruptHandler.o \
kernel/interrupt/keyboardService.o kernel/interrupt/keyboardResolution.o \
kernel/syscall/getTicks.o kernel/syscall/getTicksService.o kernel/syscall/write.o kernel/syscall/writeService.o kernel/lib/printf.o \
kernel/syscall/printx.o kernel/syscall/printxService.o kernel/syscall/sendrec.o kernel/syscall/sendrecService.o


.PHONY		:	all everything cleanAllBin cleanAllO buildImg

all			:	cleanAllBin cleanAllO everything cleanAllO
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

booter/bootSector.bin				:	booter/bootSector.asm  booter/include/LoadingAddress.inc booter/include/FAT12header.inc booter/include/RealModeLib.inc
										${ASM} ${ASMBFLAGS}	-o $@ $<
booter/Loader.bin					:	booter/Loader.asm booter/include/LoadingAddress.inc	booter/include/FAT12header.inc booter/include/ProtectMode.inc booter/include/RealModeLib.inc
										${ASM}	${ASMBFLAGS} -o $@ $<
kernel/Kernel.bin					:	${OBJS}
										${LD} ${LDFLAGS} -o Kernel.bin ${OBJS}

#SourceCode/kernel/
kernel/Kernel.o						:	kernel/Kernel.asm 
										${ASM} ${ASMKFLAGS} -o $@ $<
kernel/start.o						:	kernel/start.c kernel/include/type.h kernel/include/const.h kernel/include/important.h kernel/include/global.h kernel/include/prototype.h
										${CC} ${CFLAGS} -o $@ $<
kernel/global.o						:	kernel/global.c  kernel/include/global.h
										${CC} ${CFLAGS} -o $@ $<
kernel/processDemo.o				:	kernel/processDemo.c kernel/include/type.h kernel/include/prototype.h
										${CC} ${CFLAGS} -o $@ $<
kernel/process.o					:	kernel/process.c kernel/include/type.h kernel/include/prototype.h
										${CC} ${CFLAGS} -o $@ $<
kernel/tty.o                        :   kernel/tty.c kernel/include/type.h kernel/include/prototype.h				
										${CC} ${CFLAGS} -o $@ $<
kernel/console.o                    :   kernel/console.c kernel/include/console.h
										${CC} ${CFLAGS} -o $@ $<
kernel/mistake.o                    :   kernel/mistake.c 
										${CC} ${CFLAGS} -o $@ $<

#SourceCode/kernel/systemtask									
kernel/systemtask/sys_tty.o         :	kernel/systemtask/sys_tty.c
										${CC} ${CFLAGS} -o $@ $<
kernel/systemtask/sys_task.o        :   kernel/systemtask/sys_task.c
										${CC} ${CFLAGS} -o $@ $<
										


#SourceCode/kernel/lib
kernel/lib/delay.o						:	kernel/lib/delay.c	kernel/include/type.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<
kernel/lib/dispInt.o					:	kernel/lib/dispInt.c kernel/include/type.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<
kernel/lib/display.o					:	kernel/lib/display.asm
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/lib/openIrq.o					:	kernel/lib/openIrq.c kernel/include/type.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<
kernel/lib/operatePort.o				:	kernel/lib/operatePort.asm 
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/lib/string.o						:	kernel/lib/string.asm
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/lib/interrupt.o					:	kernel/lib/interrupt.asm
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/lib/printf.o                     :   kernel/lib/printf.c
											${CC} ${CFLAGS} -o $@ $<







#SourceCode/kernel/init
kernel/init/initClock.o					:	kernel/init/initClock.c kernel/include/type.h kernel/include/global.h kernel/include/intVector.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<
kernel/init/init8259A.o					:	kernel/init/init8259A.c kernel/include/type.h kernel/include/const.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<
kernel/init/initDescriptor.o			:	kernel/init/initDescriptor.c kernel/include/type.h kernel/include/important.h
											${CC} ${CFLAGS} -o $@ $<
kernel/init/initIDT.o					:	kernel/init/initIDT.c kernel/include/type.h kernel/include/global.h kernel/include/intVector.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<
kernel/init/initLDTDescriptor.o			:	kernel/init/initLDTDescriptor.c kernel/include/type.h kernel/include/global.h kernel/include/important.h kernel/include/prototype.h kernel/include/process.h
											${CC} ${CFLAGS} -o $@ $<
kernel/init/initPCB.o					:	kernel/init/initPCB.c kernel/include/type.h kernel/include/global.h kernel/include/prototype.h kernel/include/process.h kernel/include/important.h 
											${CC} ${CFLAGS} -o $@ $<
kernel/init/initTSSDescriptor.o			:	kernel/init/initTSSDescriptor.c kernel/include/type.h kernel/include/global.h kernel/include/prototype.h kernel/include/important.h
											${CC} ${CFLAGS} -o $@ $<
kernel/init/initVariable.o              :   kernel/init/initVariable.c  kernel/include/global.h
											${CC} ${CFLAGS} -o $@ $<
kernel/init/initKeyboard.o              :   kernel/init/initKeyboard.c  kernel/include/type.h kernel/include/global.h kernel/include/intVector.h kernel/include/prototype.h


#SourceCode/kernel/interrupt
kernel/interrupt/exceptionHandler.o		:	kernel/interrupt/exceptionHandler.c kernel/include/type.h kernel/include/global.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<
kernel/interrupt/clockService.o         :   kernel/interrupt/clockService.c 
											${CC} ${CFLAGS} -o $@ $<
kernel/interrupt/interruptHandler.o		:	kernel/interrupt/interruptHandler.asm
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/interrupt/keyboardService.o      :   kernel/interrupt/keyboardService.c kernel/include/type.h kernel/include/global.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<
kernel/interrupt/keyboardResolution.o   :	kernel/interrupt/keyboardResolution.c kernel/include/type.h kernel/include/global.h kernel/include/prototype.h
											${CC} ${CFLAGS} -o $@ $<						
#SouceCode/kernel/syscall
kernel/syscall/getTicks.o				:	kernel/syscall/getTicks.asm
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/syscall/getTicksService.o        :	kernel/syscall/getTicksService.c 
											${CC} ${CFLAGS} -o $@ $<
kernel/syscall/write.o					:	kernel/syscall/write.asm
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/syscall/writeService.o           :	kernel/syscall/writeService.c
											${CC} ${CFLAGS} -o $@ $<
kernel/syscall/printx.o                 :   kernel/syscall/printx.asm
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/syscall/printxService.o          :   kernel/syscall/printxService.c
											${CC} ${CFLAGS} -o $@ $<
kernel/syscall/sendrec.o                :   kernel/syscall/sendrec.asm
											${ASM} ${ASMKFLAGS} -o $@ $<
kernel/syscall/sendrecService.o         :   kernel/syscall/sendrecService.c 									
											${CC} ${CFLAGS} -o $@ $<
