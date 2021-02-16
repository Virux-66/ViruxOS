#ifndef _IMPORTANT_H
#define _IMPORTANT_H

#include "type.h"

typedef struct gate_descriptor
{
	u16		offsetLow;
	u16     selector;
	u8      attr1;
	u8      attr2;
	u16     offsetHigh;
}Gate;
typedef struct segment_descriptor
{
	u16		limitLow;
	u16     baseLow;
	u8      basehigh1;
	u8      attr1;
	u8      limitHigh_attr2;
	u8      baseHigh2;
}Descriptor;
typedef struct TaskStatusSegment {
	u32 backlink;
	u32 esp0;
	u32 ss0;
	u32 esp1;
	u32 ss1;
	u32 esp2;
	u32 ss2;
	u32 cr3;
	u32 eip;
	u32 flags;
	u32 eax;
	u32 ecx;
	u32 edx;
	u32 ebx;
	u32 esp;
	u32 ebp;
	u32 esi;
	u32 edi;
	u32 es;
	u32 cs;
	u32 ss;
	u32 ds;
	u32 fs;
	u32 gs;
	u32 ldt;
	u16 trap;
	u16 iobase;
}TSS;



//descriptor attribute
#define		DA_32		0x4000
#define		DA_4K		0x8000
#define		DA_P		0x80
#define		DA_NP		0x00
#define		DA_S		0x10
#define		DA_NS		0x00
//descriptor privilege
#define		DA_DPL_0	0x00
#define		DA_DPL_1	0x20
#define		DA_DPL_2	0x40
#define		DA_DPL_3	0x60
//descriptor type
//data type 
#define		DA_D_0		0x00	//data segment read-only
#define		DA_D_E		0x04	//ds extensive 
#define		DA_D_W		0x02	//ds writable
#define		DA_D_A		0x01	//ds accessed
//segment type
#define		DA_C_X		0x08	//code segment executable
#define		DA_C_C		0x04	//cs comforming 
#define		DA_C_R		0x02	//code readable
#define		DA_C_A		0x01	//code accessed
//system segment and gata descriptor
#define		DA_LDT		0x02	//LDT
#define		DA_TASKGATE	0x05	//task gate
#define		DA_386TSS	0x09	//386TSS
#define		DA_386CGATE	0x0c	//386 call gate
#define		DA_386IGATE	0x0e	//386 interrupt gate
#define		DA_386TGATE	0x0f

//selector attribute
#define		SA_GDT		0
#define		SA_LDT		4
#define		SA_RPL0		0
#define		SA_RPL1		1
#define		SA_RPL2		2
#define		SA_RPL3		3

//selectors in GDT, in my opinion, these are static and go against 
// dynamic processes loading.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define SELECTOR_DUMMY		0x00
#define SELECTOR_FLAT_C		0x08
#define SELECTOR_FLAT_RW	0x10
#define SELECTOR_VIDEO		(0x18+3)
#define SELECTOR_TSS		0x20
#define SELECTOR_LDT_FIRST	0x28

#define INDEX_DUMMY		0
#define INDEX_FLAT_C	1
#define INDEX_FLAT_RW	2
#define INDEX_VIDEO		3
#define	INDEX_TSS		4
#define INDEX_LDT_FIRST	5


#endif