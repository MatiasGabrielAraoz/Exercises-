#include <cstddef>
#include <iostream>
#include <string>


int main(){
	int amountOfSquares;
	std::string amountOfSquaresStr;
	std::cin >> amountOfSquaresStr;
	amountOfSquares = std::stoi(amountOfSquaresStr);
	std::string inputs[amountOfSquares * 4];
	for (int i = 0; i <= amountOfSquares; i++){
		std::string input;
		std::cin >> input;
		inputs[i] = input;
		input = "";
	}

	return 0;
}
