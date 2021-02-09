#ifndef _IMPORTANT_H
#define _IMPORTANT_H
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
#endif
