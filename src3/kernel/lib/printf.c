#include "type.h"
#include "prototype.h"


PRIVATE char* i2a(int val, int base, char** ps);
PUBLIC int printf(const char* fmt, ...) {
	int i;
	char buf[256];
	char* arg = (char*)((char*)&fmt + 4);
	i = convert(buf, fmt, arg);
	printx(buf);
	return i;
}

/*PUBLIC int convert(char* buf, const char* fmt, char* arg) {
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
}*/

PUBLIC int convert(char* buf, const char* fmt, char* args)
{
	char* p;

	char*	p_next_arg = args;
	int	m;

	char	inner_buf[256];
	char	cs;
	int	align_nr;

	for (p = buf; *fmt; fmt++) {
		if (*fmt != '%') {
			*p++ = *fmt;
			continue;
		}
		else {		/* a format string begins */
			align_nr = 0;
		}

		fmt++;

		if (*fmt == '%') {
			*p++ = *fmt;
			continue;
		}
		else if (*fmt == '0') {
			cs = '0';
			fmt++;
		}
		else {
			cs = ' ';
		}
		while (((unsigned char)(*fmt) >= '0') && ((unsigned char)(*fmt) <= '9')) {
			align_nr *= 10;
			align_nr += *fmt - '0';
			fmt++;
		}

		char* q = inner_buf;
		memset(q, 0, sizeof(inner_buf));

		switch (*fmt) {
		case 'c':
			*q++ = *((char*)p_next_arg);
			p_next_arg += 4;
			break;
		case 'x':
			m = *((int*)p_next_arg);
			i2a(m, 16, &q);
			p_next_arg += 4;
			break;
		case 'd':
			m = *((int*)p_next_arg);
			if (m < 0) {
				m = m * (-1);
				*q++ = '-';
			}
			i2a(m, 10, &q);
			p_next_arg += 4;
			break;
		case 's':
			strcpy(q, (*((char**)p_next_arg)));
			q += strlen(*((char**)p_next_arg));
			p_next_arg += 4;
			break;
		default:
			break;
		}

		int k;
		for (k = 0; k < ((align_nr > strlen(inner_buf)) ? (align_nr - strlen(inner_buf)) : 0); k++) {
			*p++ = cs;
		}
		q = inner_buf;
		while (*q) {
			*p++ = *q++;
		}
	}

	*p = 0;

	return (p - buf);
}



PRIVATE char* i2a(int val, int base, char** ps)
{
	int m = val % base;
	int q = val / base;
	if (q) {
		i2a(q, base, ps);
	}
	*(*ps)++ = (m < 10) ? (m + '0') : (m - 10 + 'A');

	return *ps;
}