#ifndef _TYPH_H_
#define _TYPH_H_


typedef unsigned long long u64;
typedef unsigned int    u32;
typedef unsigned short  u16;
typedef unsigned char   u8;

// function pointer
typedef void (*intHandler)();
typedef void (*taskFunction)();
typedef void (*irqService)(int irq);
typedef void* systemCall;

#define	PUBLIC
#define	PRIVATE	static
#define EXTERN	extern



#endif // !_TYPH_H_

