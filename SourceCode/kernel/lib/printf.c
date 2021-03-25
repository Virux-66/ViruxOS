#include "type.h"
#include "prototype.h"

//PRIVATE int convert(char* buf, const char* fmt, char* arg);

PUBLIC int printf(const char* fmt, ...) {
	int i;
	char buf[256];
	char* arg = (char*)((char*)&fmt + 4);
	i = convert(buf, fmt, arg);
	printx(buf);
	return i;
}

PUBLIC int convert(char* buf, const char* fmt, char* arg) {
	char* p;
	char tmp[256];
	char* pArg = arg;
	int length = 0;
	for (p = buf; *fmt; fmt++) {
		if (*fmt != '%') {
			*p++ = *fmt;
			continue;
		}
		fmt++;
		switch (*fmt)
		{
		case 'c':
			*p++ = *((char*)pArg);
			pArg += 4;
			break;
		case 'x':
			itoa(tmp, *((int*)pArg));
			for (int k = 0; k < 256; k++) {
				if (tmp[k] == 0) {
					length = k;
					break;
				}
			}
			memcpy(p, tmp, length);
			pArg += 4;
			p += length;
			break;
		case 's':
			for (char* ps = *((char**)arg); *ps; ps++) 
				*p++ = *ps;
			pArg += 4;
			break;
		default:
			break;
		}
	}
	return p - buf;
}