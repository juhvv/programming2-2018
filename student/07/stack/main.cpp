#include "stack.hh"
#include <iostream>

using namespace std;

int main()
{
    Stack s;
    int elem = 0;

    if(s.pop(elem)) {
        cout << elem << endl;
    } else {
        cout << "The stack has no top element" << endl;
    }

    s.push(1);
    if(s.pop_second_top(elem)) {
        cout << "Second top element: " << elem << endl;
    } else {
        cout << "The stack has no second top element: ";
        s.print();
    }

    s.push(2);
    s.push(3);
    s.print();
    if(s.pop_second_top(elem)) {
        cout << "Second top element: " << elem << endl;
    } else {
        cout << "The stack has no second top element: ";
        s.print();
    }

    s.print();

    return EXIT_SUCCESS;
}
