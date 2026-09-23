#include "main.h"

void _start(){
	int fd = asm_fopen("text", O_RDONLY);
	int size = 64;
	char buf[size];
	asm_fread(fd, buf, size);

	print("%s \n", buf);

	asm_exit();
}
