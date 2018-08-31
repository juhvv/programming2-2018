#include <iostream>

const unsigned int MAX = 33;

int main()
{
    unsigned int inpt_num = 0;
    std::cout << "Enter a positive integer (from interval [1.." << MAX << "]): ";
    std::cin >> inpt_num;

    if ( inpt_num <= MAX ) {
        unsigned int factorial = inpt_num;
        if ( inpt_num != 0 ) {
            unsigned int temp_val = inpt_num;
            while ( temp_val > 1) {
                temp_val -= 1;
                factorial = factorial * ( temp_val );
            }
        } else {
            factorial = 1;
        }

        std::cout << "Factorial of " << inpt_num << " is "<< factorial << std::endl;

    } else {
        std::cout << "Too big number" << std::endl;
    }
}
