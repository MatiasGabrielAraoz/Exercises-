#pragma once
#include "include/main.h"
#include <math.h>

Vector2 AddVectors(Vector2 v1, Vector2 v2){
	return (Vector2){v1.x + v2.x, v1.y + v2.y};
}

Vector2 SubVectors(Vector2 v1, Vector2 v2){
	return (Vector2){v1.x - v2.x, v1.y - v2.y};
}

float sind(float x){
	return sinf(x * M_PI / 180);
}
float cosd(float x){
	return cosf(x * M_PI / 180);
}

// multiplica una matrix con x cantidad de columnas y filas con otra matriz
void multiplyMatrix(int A_rows, int A_cols, int B_cols, float A[A_rows][A_cols], float B[A_cols][B_cols], float dest[A_rows][B_cols]) {
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            dest[i][j] = 0;
            for (int k = 0; k < A_cols; k++) {
                dest[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// devuelve la transpuesta de una matriz
void transpose(int rows, int columns, float matrix[rows][columns], float dest[columns][rows]){
	for (int row = 0; row < rows; row++){
		for (int col = 0; col < columns; col++){
			dest[col][row] = matrix[row][col];
		}
	}
}

float Get2x2Determinant(float matrix[2][2]){
	return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
}

void invert2x2Matrix(float matrix[2][2], float dest[2][2]){
	float det = Get2x2Determinant(matrix);
	float A = matrix[0][0];
	float B = matrix[0][1];
	float C = matrix[1][0];
	float D = matrix[1][1];
	
	dest[0][0] = D / det;
	dest[0][1] = -B / det;
	dest[1][0] = -C / det;
	dest[1][1] = A / det;
}

void moorePenrose(int rows, int columns, float J[rows][columns], float out[columns][rows]){

	// transpuesta de J
	float JT[columns][rows];
	transpose(rows, columns, J, JT);

	// J x transpuesta
	float JJT[rows][rows];
	multiplyMatrix(rows, columns, columns, J, JT, JJT);

	// inversa de J x transpuesta
	float JJI[rows][rows];
	invert2x2Matrix(2, JJT, JJI);

	// transpuesta x JJI
	multiplyMatrix(columns, rows, rows, JT, JJI, out);

}
