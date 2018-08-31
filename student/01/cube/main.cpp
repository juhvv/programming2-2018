#include <iostream>
#include <cmath>

int main()
{
    int inpt_num = 0;
    std::cout << "Enter a number: ";
    std::cin >> inpt_num;

    int result = pow( inpt_num, 3);

    if ( result >= inpt_num and result > 0) {
        std::cout << "The cube of " << inpt_num << " is " << result << "." << std::endl;
    } else {
        std::cout << "Error! The cube of " << inpt_num << " is not " << result << "." << std::endl;
    }
}
