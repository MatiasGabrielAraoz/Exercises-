#include <ada/expected.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

int main(){
	int nroent;
	std::printf("escribi un numero: ");
	std::cin >> nroent;
	if (nroent > 0) {
		std::printf("es positivo");
	
	}
	else {
		if (nroent < 0) {
			std::printf("no es positivo");
		}
		else {
			std::printf("es cero");
		}	
	}
}
