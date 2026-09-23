#include <iostream>

using namespace std;

int main(){
	int correctos, incorrectos, mult5 = 0;

	for (size_t i = 0; i <= 5; i++){
		cout << "Inserta un valor";
		int tmp;
		cin >> tmp;

		if (tmp > 0) correctos++;
		else incorrectos++;

		if (tmp % 5 == 0) mult5++;
	}
	cout << "correctos: " << correctos << '\n';
	cout << "incorrectos: " << incorrectos << '\n';
	cout << "multiplos de 5: " << mult5 << '\n';

	return 0;
}
