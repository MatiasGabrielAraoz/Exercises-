#include <stdio.h>

int fileLen(FILE* file){
	fpos_t start_pos;
	fgetpos(file, &start_pos);

	fseek(file, 0, SEEK_END);
	int length = ftell(file);

	fsetpos(file, &start_pos);

	return length;
}

int main(int argc, char** argv){
	if (argc <= 2){
		fprintf(stderr,"Faltan argumentos, el primer argumento indica el archivo de entrada y el segundo el de salida");
		return -1;
	}

	char* inputFileName = argv[1];
	char* outputFileName = argv[2];

	FILE* input = fopen(inputFileName, "rb");
	FILE* output = fopen(outputFileName, "wb");

	if (input == NULL || output == NULL){
		fprintf(stderr, "No se pudieron abrir los archivos");		
		return -1;
	}
	
	printf("Inserta el valor para encriptarlo: ");
	char keyStr[32];
	int key;
	scanf("%s", keyStr);
	sscanf(keyStr, "%i", &key);

	int batchSize = 1024;
	char inputBuffer[batchSize];
	char outputBuffer[batchSize];

	while (1==1){
		size_t bytesRead = fread(inputBuffer, sizeof(char), batchSize, input);
		if (bytesRead == 0) break;

		for (size_t j = 0; j < bytesRead; j++){
			outputBuffer[j] = inputBuffer[j] ^ key;						
			printf("%c", inputBuffer[j] ^ key);
		}

		fwrite(outputBuffer, sizeof(char), bytesRead, output);
	}
	fclose(input);
	fclose(output);
}
