#include <stdio.h>

int main(int argc, char** argv){
	if (argc <= 2) {
		fprintf(stderr, "Faltan argumentos");
		return -1;
	}
	char* fileName = argv[1];
	char* text = argv[2];
	
	FILE* file = fopen(fileName, "a");

	if (file == NULL){
		fprintf(stderr,"No se pudo abrir el archivo");
		return -1;
	}

	fprintf(file, "%s", text);


}
