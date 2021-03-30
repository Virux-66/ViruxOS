#ifndef _MESSAGE_H
#define _MESSAGE_H
#include "package.h"

struct mess1 {//16B
	int m1i1;
	int m1i2;
	int m1i3;
	int m1i4;
};
struct mess2 {//16B
	void* m2p1;
	void* m2p2;
	void* m2p3;
	void* m2p4;
};
struct mess3 {//80B
	int m3i1;
	int m3i2;
	int m3i3;
	int m3i4;
	u64 m3l1;
	u64 m3l2;
	u64 m3l3;
	u64 m3l4;
	u64 m3l5;
	u64 m3l6;
	u64 m3l7;
	void* m3p1;
};

typedef struct {										//128B
	int source;
	int dest;
	int type;
	int reply;													//when reply = 1 , it means service requested has done;
	PACKAGE* pPackage;
	union {
		struct mess1 m1;
		struct mess2 m2;
		struct mess3 m3;
	}u;
}MESSAGE;




#endif