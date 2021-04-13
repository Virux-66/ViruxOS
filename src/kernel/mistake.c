#include "type.h"
#include "const.h"
#include "prototype.h"

PUBLIC void spin(char* funcName) {
	printf("\nspinning in %s...\n", funcName);
	while (1) {};
}



PUBLIC void assertionFailure(char* exp,char* file,char*base_file,int line) {
	/*printf("file:%s\n", file);
	printf("base_file:%s\n", base_file);
	printf("line:%x\n", line);*/


	printf("%c  assert() failed: file: %s, base_file: %s, line: %x",
		MAG_CH_ASSERT,  file, base_file, line);
	spin("assertFailure()");
}

PUBLIC void panic(const char* fmt,...) {
	int i;
	char buf[256];

	char* arg = (char*)((char*)&fmt + 4);
	i = convert(buf, fmt, arg);
	printf("%c !!panic!! %s", MAG_CH_PANIC, buf);
}