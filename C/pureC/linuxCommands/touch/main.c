#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv){
	if (argc <= 1){
		errno = 22;
		perror("Error");
		return -1;
	}

	FILE* file = fopen(argv[1], "w");

	fclose(file);
	return 0;
}
