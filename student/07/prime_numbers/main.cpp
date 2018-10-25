#include <iostream>
#include <vector>


int main()
{
    int ubound;
    std::cout << "Enter an upper bound: ";
    std::cin >> ubound;

    bool* primePtr = nullptr;
    bool primes[ubound];
    primePtr = primes;

    int num = 0;
    while ( num < ubound ) {
        if (num == 0 or num == 1) {
            *primePtr = false;
        } else if ((num % 2 == 0 or num % 3 == 0 or num % 5 == 0 or num % 7 == 0 or num % 11 == 0) and (num != 2 and num != 3 and num != 5 and num != 7 and num != 11)) {
            *primePtr = false;
        } else {
            *primePtr = true;
        }


        ++primePtr;
        ++num;
    }

    std::cout << "Prime numbers smaller than " << ubound << ":" << std::endl;
    int index = 0;
    while (index < ubound) {
        if (primes[index]) {
            std::cout << index << " ";
        }
        ++index;
    }
    std::cout << std::endl;

}
