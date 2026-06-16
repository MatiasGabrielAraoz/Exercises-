#include <stdio.h>
#include <errno.h>

void GetIntFromFStart(void* var, size_t size,FILE* file, int position){
	fseek(file, position, SEEK_SET);
	fread(var, size, 1, file);
}

int main(int argc, char** argv){
	if (argc <= 2){
		errno = 22; // err invalid argument
		perror("Error, no especificaste un archivo a transformar y destino a transformar");
		return -1;
	}
	char* inputImgStr = argv[1];
	char* outputImgStr = argv[2];

	FILE* Finput = fopen(inputImgStr, "rb");
	FILE* Foutput = fopen(outputImgStr, "wb");

	if (Finput == NULL){
		perror("No se pudo abrir el archivo");
	}

	unsigned char signature[2];
	fread(signature, sizeof(char), 2, Finput);

	if (signature[0] != 'B' || signature[1] != 'M'){
		errno = 124;
		perror("Error, el archivo no es un bitmap");
	}
	int imgWidth, imgHeight, colorArrPosition;
	short bpp;

	// la posición del array de colores está en el byte 10
	GetIntFromFStart(&colorArrPosition, sizeof(int),Finput, 10);

	// width está guardado en el byte 18
	GetIntFromFStart(&imgWidth, sizeof(int),Finput, 18);

	// height está guardado en el byte 22
	GetIntFromFStart(&imgHeight, sizeof(int),Finput, 22);

	// bits por pixel estpa guardado en el byte 28
	GetIntFromFStart(&bpp, sizeof(short),Finput, 28);

	printf("width = %d \n", imgWidth);
	printf("height = %d \n", imgHeight);
	printf("Position = %d \n", colorArrPosition);
	printf("bpp = %d \n", bpp);

	fseek(Finput, 0, SEEK_SET);

	unsigned char header[256];
	fread(header, sizeof(unsigned char), colorArrPosition, Finput);

	fwrite(header, sizeof(unsigned char), colorArrPosition, Foutput);

	fseek(Finput, colorArrPosition, SEEK_SET);

	// el ancho en bytes se calcula como ((ancho * bpp + 31)/ 32)*4 
	int bytewidth = ((imgWidth * bpp + 31) / 32) * 4;

	unsigned char buffer[imgWidth];
	for (int i = 0; i < imgWidth; i++){

	}

	fclose(Finput);
	return 0;
}
