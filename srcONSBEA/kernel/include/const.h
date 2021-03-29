#ifndef _CONST_H_
#define _CONST_H
#define	GDTSIZE		128
#define IDTSIZE		256
#define LDTSIZE		3

#define MASTER_INT_NUM 0x20
#define SLAVE_INT_NUM 0x28

#define userProcessNumber 2

#define processStackSize	0x8000

#define taskNumber	2

#define consoleNumber 3

#define sysCallNumber 4

#define V_MEM_BASE			0xB8000
#define V_MEM_SIZE			0x8000

#define MAG_CH_PANIC		'\002'
#define MAG_CH_ASSERT		'\003'

#define SENDING		0x02	//pFlags
#define RECEVING	0x04	//pFlags

//ipc type
#define SEND		1
#define RECEIVE		2
#define	BOTH		3

#define ANY		(userProcessNumber+taskNumber+10)
#define NO_TASK (userProcessNumber+taskNumber+20)

#define INTERRUPT -10

//message type
#define HARD_INT	1
#define GET_TICKS	2
#define SEG_EXC		3	
#define NEGO		4
#define COPY		5
#define ECHO		6
#define SBEA		7

#define ASSERT
#ifdef ASSERT
void assertionFailure(char* exp, char* file, char* base_file, int line);
#define assert(exp) if(exp); \
		else assertionFailure(#exp,__FILE__,__BASE_FILE__,__LINE__)
#endif // !_CONST_H_

#endif
