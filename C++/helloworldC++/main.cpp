#include <iostream>
#include <chrono>

int main(){
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << "Hola";
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	
	std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

	return 0;

}
