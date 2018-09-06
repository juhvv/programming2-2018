#include <iostream>
#include <cmath>
#include <string>

std::string calculate_combinations( unsigned long int p, unsigned long int n);

unsigned long int factorial(unsigned long int inpt_num)
{
    unsigned long int factorial = inpt_num;
    if ( inpt_num != 0 ) {
        unsigned long int temp_val = inpt_num;
        while ( temp_val > 1) {
            temp_val --;
            factorial = factorial * ( temp_val );
        }
    } else {
        factorial = 1;
    }
    return factorial;
}

bool inpt_chk(int balls, int max_balls) {
    if ( balls < 0 or max_balls < 0 ) {
        std::cout << "The number of balls must be a positive number." << std::endl;
        return 0;

    } else if ( balls == max_balls ) {
        std::cout << "The maximum number of drawn balls is the total amount of balls." << std::endl;
        return 0;

    } else {
        return 1;
    }
}

int main()
{
    int balls = 0;
    int max_balls = 0;

    std::cout << "Enter the total number of lottery balls: ";
    std::cin >> balls;

    std::cout << "Enter the number of drawn balls: ";
    std::cin >> max_balls;

    if ( inpt_chk( balls, max_balls )) {
        std::string result = calculate_combinations( balls, max_balls );
        std::cout << "The probability of guessing all " << max_balls
                  << " balls correctly is " << result << std::endl;
    }
}

std::string calculate_combinations(unsigned long int n, unsigned long int p) {
    unsigned long int top = 0;
    unsigned long int bottom = 0;

    top = factorial( n );
    bottom = factorial( ( n - p ) ) * factorial( p );
    unsigned long int res = top/bottom;

    std::string output = "1/" + std::to_string( res );

    return output;
}
