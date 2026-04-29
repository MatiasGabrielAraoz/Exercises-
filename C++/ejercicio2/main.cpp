#include <iostream>
#include <stdlib.h>


int main(){
	int nroent;
	std::cout << "escribe un numero: ";
	std::cin >> nroent;
	if (nroent < 0) {
		std::cout << "no es positivo";
	}
	else {
		std::cout << "es positivo";
	}
}
