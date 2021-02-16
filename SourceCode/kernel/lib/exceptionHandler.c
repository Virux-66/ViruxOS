#include "type.h"
#include "const.h"
#include "intVector.h"
#include "important.h"
#include "process.h"
#include "prototype.h"
#include "global.h"

PUBLIC void generalExceptionHandler(int vector, int errorCode, int eip, int cs, int eflags) {
	//0x08:0x3095d
	int i;
	int textColor = 0x74; /* »Òµ×ºì×Ö */

	char* err_msg[] = { "#DE Divide Error",
				"#DB RESERVED",
				"--  NMI Interrupt",
				"#BP Breakpoint",
				"#OF Overflow",
				"#BR BOUND Range Exceeded",
				"#UD Invalid Opcode (Undefined Opcode)",
				"#NM Device Not Available (No Math Coprocessor)",
				"#DF Double Fault",
				"    Coprocessor Segment Overrun (reserved)",
				"#TS Invalid TSS",
				"#NP Segment Not Present",
				"#SS Stack-Segment Fault",
				"#GP General Protection",
				"#PF Page Fault",
				"--  (Intel reserved. Do not use.)",
				"#MF x87 FPU Floating-Point Error (Math Fault)",
				"#AC Alignment Check",
				"#MC Machine Check",
				"#XF SIMD Floating-Point Exception"
	};
	dispPos = 0;
	for (i = 0; i < 80 * 5; i++)
		//0x08:0x30995
		dispStr(" ");			//30866
	dispPos = 0;
	dispColorStr("Exception --> ", textColor);
	dispColorStr(err_msg[vector], textColor);
	dispColorStr("\n\n", textColor);
	dispColorStr("EFLAGS:", textColor);
	dispInt(eflags);
	dispColorStr("CS:", textColor);
	dispInt(cs);
	dispColorStr("EIP:", textColor);
	dispInt(eip);
	if (errorCode != 0xffffffff) {
		dispColorStr("Error code:", textColor);
		dispInt(errorCode);
	}
}