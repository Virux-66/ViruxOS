#ifndef _ASSERT_H

#include "prototype.h"
#define _ASSERT_H
//if exp=true does nothing otherwise, terminate the program
#define assert(exp)	if(exp); \
		else assertionFailure(#exp,__FILE__,__BASE_FILE__,__LINE__)
#else
#define assert(exp)
#endif