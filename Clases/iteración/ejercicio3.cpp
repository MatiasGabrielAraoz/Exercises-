#include <iostream>

using namespace std;

#define TEMPS_AMNT 20

int main(){

	int add_temps = 0;
	for (size_t i = 0; i <= TEMPS_AMNT; i++){
		cout << "Inserta una temperatura: ";
		int tmp = 0;
		cin >> tmp;
		add_temps += tmp;
		
	}
	int avg_temps = add_temps / TEMPS_AMNT;

	return 0;
}
