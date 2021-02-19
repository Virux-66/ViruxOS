#ifndef _TYPH_H_
#define _TYPH_H_
// 
typedef unsigned int    u32;
typedef unsigned short  u16;
typedef unsigned char   u8;
// function pointer
typedef void (*intHandler)();
typedef void (*taskFunction)();
#define	PUBLIC
#define	PRIVATE	static
#define EXTERN extern
#endif // !_TYPH_H_

