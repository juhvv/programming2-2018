#include <iostream>


int main()
{
    int num_count = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> num_count;

    for ( int number = 1; number <= num_count; ++number) {
            std::cout << number << std::endl;

    }
}
