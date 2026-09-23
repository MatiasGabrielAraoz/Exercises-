#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv){
	if (argc < 2){
		errno = 22;
		perror("Error, Not enough arguments");
		return -1;
	}

	if (mkdir(argv[1], S_IRWXU | S_IRWXG | S_IRWXO ) != 0){
		perror("Error creating directory");

	}

	return 0;
}
