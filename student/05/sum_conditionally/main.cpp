#include <iostream>

unsigned int divisible_by_3_or_7(unsigned int uBound)
{
    if (uBound == 0) {
        return 0;

    } else if (uBound % 3 == 0 or uBound % 7 == 0) {
        return uBound + divisible_by_3_or_7(uBound - 1);

    } else {
        return divisible_by_3_or_7(uBound - 1);
    }
}

int main()
{
    unsigned int uBound;
    std::cout << "Enter an upper bound: ";
    std::cin >> uBound;

    std::cout << "Sum of non-negative integers between 0 and " << uBound << " and divisible by 3 or 7 is " << divisible_by_3_or_7(uBound) << std::endl;

}
