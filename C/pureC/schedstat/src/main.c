#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define NULL_TERMINATE(size, buf) ((buf)[(size) - 1] = '\0')
#define BUF_SIZE 64

int main(){
	static char buffer[BUF_SIZE + 1]; // +1 por el \0
	FILE* sched_file = fopen("/proc/schedstat", "r");
	assert(sched_file);

	fread(buffer, 10, 1, sched_file);
	NULL_TERMINATE(sizeof(buffer), buffer);
	assert(buffer[0] == 'v');

	int ver_num = 0;
	if (!sscanf(buffer, "version %d\n", &ver_num)){
		fprintf(stderr, "Error, version not found.");
		return -1;
	}
	for (size_t i = 0; i < 0; i++){
		memset(buffer, 0, BUF_SIZE);

	}
	memset(buffer, 0, BUF_SIZE);

	fseek(sched_file, 11, SEEK_SET);
	fread(buffer, BUF_SIZE, 1, sched_file);

	printf("version: %d", ver_num);


	return 0;
}
