#include "type.h"
#include "prototype.h"

PUBLIC int printf(const char* fmt, ...) {
	int i;
	char buf[256];
	char* arg = (char*)((char*)&fmt + 4);
	i = vaprintf(buf, fmt, arg);
	write(buf, i);
	return i;
}

PRIVATE vaprintf(char* buf, const char* fmt, char* arg) {

	char tmp[256];
	char* pArg = arg;
	int length = 0;
	for (char* p = buf; *fmt; fmt++) {
		if (*fmt != '%') {
			*p++ = *fmt;
			continue;
		}
		fmt++;
		switch (*fmt)
		{
		case 'x':
			itoa(tmp, *((int*)pArg));
			for (int k = 0; k < 256; k++){
				if (tmp[k] == '\0')
					length = k;
			}
			memcpy(p, tmp, length);
			pArg += 4;
			p += length;
			break;
		case 's':
			break;

		default:
			break;
		}
	}
	return p - buf;
}