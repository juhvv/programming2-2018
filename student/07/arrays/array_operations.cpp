#include "array_operations.hh"
#include <iostream>
#include <algorithm>
/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(int* itemptr, int size)
{
    int greatest_el = *itemptr;
    int* stop_ptr = itemptr + size;

    while ( itemptr < stop_ptr ) {
        if (*itemptr > greatest_el) {
            greatest_el = *itemptr;
        }
        ++itemptr;
    }
    return greatest_el;
}

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(int* itemptr, int* endptr) {
    int greatest_el = *itemptr;
    while ( itemptr < endptr ) {
        if (*itemptr > greatest_el) {
            greatest_el = *itemptr;
        }
        ++itemptr;
    }
    return greatest_el;
}

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(int* itemptr, int* endptr, int* targetptr) {
    while ( itemptr < endptr ) {
        *targetptr = *itemptr;

        ++itemptr;
        ++targetptr;
    }
}

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int* leftptr, int* rightptr) {
    std::reverse(leftptr, rightptr);
}
