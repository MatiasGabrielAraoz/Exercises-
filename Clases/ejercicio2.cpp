#include <stdlib.h>
#include <iostream>
#include <printf.h>

using namespace std;

int main(){
	int num1;
	int num2;
	cout << "Ingresa el primer numero entero: ";
	cin >> num1;

	cout << "Ingresa el segundo número entero: ";
	cin >> num2;

	printf("Suma: %d \nDiferencia: %d \nProducto: %d\nDivision: %d\nResto: %d\n", 
		num1 + num2,
		num1 - num2,
		num1 * num2, 
		num1 / num2,
		num1 % num2
	);

	return 0;
}
