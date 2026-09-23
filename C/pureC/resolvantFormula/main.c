#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

typedef struct {
	double x1;
	double x2;
} Results;

Results resolvant(float a, float b, float c){
	float discriminant = sqrtf(powf(b, 2) - 4 * a * c);
	if ( isnan(discriminant) ){
		printf("La discriminante no puede ser negativa");
		return (Results){-1, -1};
	}

	float x1 = (-b + discriminant) / 2;
	float x2 = (-b - discriminant) / 2;

	Results res = (Results){x1, x2};
	return res;
}

int main(int argc, char** argv){
	if (argc < 4){
		errno = 22;
		perror("Faltan argumentos");
	}
	float a, b, c;

	a = atof(argv[1]);
	b = atof(argv[2]);
	c = atof(argv[3]);

	Results results = resolvant(a, b, c);
	if (results.x1 == -1 && results.x2 == -1){
		return -1;
	}
	printf("x1 = %.5f \n", results.x1);
	printf("x2 = %.5f \n", results.x2);
	resolvant(a, b, c);
	

	return 0; 
}
