#include "swap.hh"

// TODO: Implement swap function here

void swap(int& i, int& j) {
    int temp = j;
    j = i;
    i = temp;
}
