#include <iostream>


int main()
{
    int num_count = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> num_count;

    for ( int number = 1; number <= num_count; ++number) {

        if ( number%3 == 0) {
            std::cout << "zip" << std::endl;
        } else if ( number%7 == 0 ) {
            std::cout << "boing" << std::endl;
        } else {
            std::cout << number << std::endl;
        }
    }
}
