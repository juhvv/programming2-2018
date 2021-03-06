#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here
bool same_values(std::vector<int> integers);
bool is_ordered_ascending(std::vector<int> integers);
bool is_arithmetic_series(std::vector<int> integers);
bool is_geometric_series(std::vector<int> integers);

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_ascending(integers))
        std::cout << "The integers are in an ascending order" << std::endl;
    else
        std::cout << "The integers are not in an ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}

bool same_values(std::vector<int> integers)
{
    int const_val = integers.at(0);

    for (int integer : integers) {
        if (integer != const_val) {
            return 0;
        }
    }
    return 1;
}

bool is_ordered_ascending(std::vector<int> integers)
{
    int prev_val = integers.at(0);

    for (int integer : integers) {
        if (integer < prev_val) {
            return 0;
        }
    }
    return 1;
}

bool is_arithmetic_series(std::vector<int> integers)
{
    int first = integers.at(0);
    int second = integers.at(1);
    int d = second - first;

    int n = 1;
    for (int integer : integers) {
        if (integer != (first + (n-1)*d)) {
            return 0;
        }
        n += 1;
    }
    return 1;
}

bool is_geometric_series(std::vector<int> integers)
{
    int first = integers.at(0);
    int second = integers.at(1);
    double q = second/first;

    int n = 1;
    for (int integer : integers) {
        if (integer != first*pow(q, n-1)) {
            return 0;
        }
        n += 1;
    }
    return 1;
}
