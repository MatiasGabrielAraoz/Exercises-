#include <iostream>

std::string isPrime(int n) {
    if (n <= 1) return "No Primo";
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return "No Primo";
        }

    }
    return "Primo";
}

int main() {
   for (int i = 0; i < 100; i++) {
       std::cout << i << isPrime(i) << std::endl;
   }
}