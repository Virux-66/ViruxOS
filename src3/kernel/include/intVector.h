#ifndef _INTVECTOR_H
#define _INTVECTOR_H

#define MASTER_INT_NUM		0x20
#define SLAVE_INT_NUM		0x28

#define INT_VECTOR_DE		0x00
#define INT_VECTOR_DB		0x01
#define INT_VECTOR_NMI		0x02
#define INT_VECTOR_BP		0x03
#define INT_VECTOR_OF		0x04
#define INT_VECTOR_BR		0x05
#define INT_VECTOR_UD		0x06
#define INT_VECTOR_NM		0x07
#define INT_VECTOR_DF		0x08
#define INT_VECTOR_SEG		0x09
#define INT_VECTOR_TS		0x0a
#define INT_VECTOR_NP		0x0b
#define INT_VECTOR_SS		0x0c
#define INT_VECTOR_GP		0x0d
#define INT_VECTOR_PF		0x0e
#define INT_VECTOR_SAVE		0x0f
#define INT_VECTOR_MF		0x10

#define INT_VECTOR_SYSCALL	0x90
#endif	