#include "type.h"
#include "prototype.h"


PUBLIC char* itoa(char* str, int num) { //transform num into hex string ending with '/0'
	char* p = str;
	char ch;
	int flag = 0;
	int bit;
	*p = '0';
	p++;
	*p = 'x';
	p++;
	if (num == 0) {
		*p = '0';
		p++;
		//return p;
	}
	else {
		
		for (int i = 28; i >= 0; i -= 4) {
			bit = num >> i;
			bit = bit & 0x0f;
			if (flag || bit) {
				flag = 1;
				ch = '0' + bit;
				if (bit > 9)
					ch += 7;
				*p = ch;
				p++;
			}
		}
	}
	*p = 0;
	return p;
}

PUBLIC void dispInt(int num) {
	char str[16];
	itoa(str, num);
	dispStr(str);
}