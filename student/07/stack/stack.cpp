#include "stack.hh"
#include <iostream>

// Implement stack operations here

// Constructor
Stack::Stack(): stack_top_(nullptr) {

}

// Destructor
Stack::~Stack()
{
    while (stack_top_ != nullptr) {
        Stack_item* itemToBeRemoved = stack_top_;

        stack_top_ = stack_top_->next;
        delete itemToBeRemoved;
    }
}

// add new element to top
void Stack::push(int item)
{
    Stack_item* newItem = new Stack_item{item, stack_top_};
    stack_top_ = newItem;
}

// remove top element, returns false if stack is empty, else true
bool Stack::pop(int &item)
{
    if (stack_top_ != nullptr) {
        item = stack_top_->item;
        Stack_item* itemToBeRemoved = stack_top_;

        stack_top_ = itemToBeRemoved->next;
        delete itemToBeRemoved;

        return true;

    } else {
        return false;
    }
}

// remove second top element, returns false if stack has less than two elements, else true
bool Stack::pop_second_top(int &item)
{
    // check that stack has at least two elements
    if (stack_top_ != nullptr and stack_top_->next != nullptr) {
        item = stack_top_->next->item;
        Stack_item* itemToBeRemoved = stack_top_->next;
        Stack_item* thirdElem = itemToBeRemoved->next;

        stack_top_->next = thirdElem;

        delete itemToBeRemoved;

        return true;

    } else {
        return false;
    }
}

// prints values of all stack elements
void Stack::print()
{
    std::cout << "Stack elements from top to bottom: ";
    if (stack_top_ != nullptr) {recursive_print(stack_top_, std::cout);}
    std::cout << std::endl;
}

// recursive function for printing element values
void Stack::recursive_print(Stack::Stack_item *item, std::ostream &s)
{
    s << item->item << " ";
    if (item->next != nullptr) {
        recursive_print(item->next, s);
    }
}


