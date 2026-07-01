#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL.h>

#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255

typedef struct {
	SDL_Point position;
	float length;
	float angle;
} Arm;

typedef struct {
	float x;
	float y;
} Vector2;

Vector2 AddVectors(Vector2 v1, Vector2 v2); 
Vector2 SubVectors(Vector2 v1, Vector2 v2); 


// multiplica una matrix con x cantidad de columnas y filas con otra matriz de x cantidad de columnas y la misma cantidad de filas
void multiplyMatrix(int A_rows, int A_cols, int B_cols, float A[A_rows][A_cols], float B[A_cols][B_cols], float dest[A_rows][B_cols]);
// devuelve la transpuesta de una matriz
void transpose(int rows, int columns, float matrix[rows][columns], float dest[columns][rows]);
// devuelve la pseudoinversa de moorePenrose
void moorePenrose(int rows, int columns, float J[rows][columns], float out[columns][rows]);
// invierte una matriz de 2x2
void invert2x2Matrix(float matrix[3][2], float dest[2][2]);
// devuelve la determinante de una matriz 2x2
float Get2x2Determinant(float matrix[2][2]);

float sind(float x);
float cosd(float x);

typedef struct {
	Arm* arms;
	Vector2 objetive;
	Vector2 error;
	size_t armsAmount;
	int argc;
	char** argv;

} AppData;
