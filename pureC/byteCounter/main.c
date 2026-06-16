#include <stdio.h>

int main(int argc, char** argv){
	if (argc <= 1){
		fprintf(stderr, "No se especificó ningún archivo");
		return -1;
	}
	char* filename = argv[1];

	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		fprintf(stderr,"el archivo %s no se pudo abrir", filename);
		return -1;
	}

	fseek(file, 0, SEEK_END);
	
	int length = ftell(file);
	if (length == -1){
		fprintf(stderr, "Error con el largo del archivo");
		return -1;
	}
	printf("El archivo mide %d bytes \n", length);

	fclose(file);
	return 0;
}
