#include "cards.hh"
#include <iostream>

// TODO: Implement the methods here

// Dynamic structure must have a constructor
// that initializes the top item as null
Cards::Cards(): top_(nullptr)
{
}

// Dynamic data structure must have a destructor
// that can be called to deallocate memory,
// when the data structure is not needed any more.
Cards::~Cards()
{
    while (top_ != nullptr) {
        Card_data* cardToBeRemoved = top_;

        top_ = top_->next;
        delete cardToBeRemoved;
    }
}

// recursive function for finding second last element of list
Cards::Card_data *Cards::get_second_last(Cards::Card_data* thisCard)
{
    if (thisCard->next->next == nullptr) {
        return thisCard;

    } else {
        return get_second_last(thisCard->next);
    }
}

int Cards::recursive_print_reverse(Cards::Card_data *top, std::ostream &s, int& n)
{
    if (top->next == nullptr) {
        //s << n << ": " << top->data << std::endl;
        ++n;
        return top->data;

    } else {
        s << n << ": " << recursive_print_reverse(top->next, s, n) << std::endl;
        ++n;
        return top->data;
    }
}

void Cards::recursive_print(Cards::Card_data* top, std::ostream &s, int n)
{
    ++n;
    s << n << ": " << top->data << std::endl;
    if (top->next != nullptr) {
        recursive_print(top->next, s, n);
    }
}


// Adds a new card with the given id as the topmost element
void Cards::add(int id)
{
    Card_data* newCard = new Card_data{id, top_};
    top_ = newCard;
}

// Prints the content of the data structure with ordinal numbers
// to the output stream given as a parameter starting from the first element
void Cards::print_from_top_to_bottom(std::ostream& s)
{
    if (top_ != nullptr) {
        recursive_print(top_, s, 0);
    }

}

// Removes the topmost card and returns it as reference parameter number.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id)
{
    // check if list is empty
    if (top_ == nullptr) {
        return false;

    } else {
        // create second pointer that points to first element of list (this case: element to be removed)
        Card_data* cardToBeRemoved = top_;
        // change value of reference parameter to value ('int data') of the first element (card)
        id = cardToBeRemoved->data;

        // change target of pointer 'top_'
        if (top_->next == nullptr) {
            // if list only has one element, set 'top_' to point nowhere
            top_ = nullptr;

        } else {
            // if list has more than one element, set 'top_' to point to second element of list ('top_->next')
            top_ = top_->next;
        }
        // only now unallocate data located in address pointed to by 'cardToBeRemoved' (previously 'top_', not
        // anymore since 'top_' was redirected in previous lines)
        delete cardToBeRemoved;

        return true;
    }
}

// Moves the last element of the data structure as the first one.
bool Cards::bottom_to_top()
{
    if (top_ != nullptr and top_->next != nullptr) {
        // get important addresses
        Cards::Card_data* secondLast = get_second_last(top_);
        Cards::Card_data* last = secondLast->next;
        Cards::Card_data* first = top_;

        //std::cout << "second last card: " << secondLast->data << std::endl;

        // start moving cards
        // last card is now top card
        top_ = last;
        // 'first' is now second card
        top_->next = first;
        // second last card is now last card,  point 'next' nowhere
        secondLast->next = nullptr;

        return true;

    } else {
        return false;
    }
}

// Moves the first element of the data structure as the last one.
bool Cards::top_to_bottom()
{
    if (top_ != nullptr and top_->next != nullptr) {
        // get important addresses
        Cards::Card_data* secondLast = get_second_last(top_);
        Cards::Card_data* last = secondLast->next;
        Cards::Card_data* first = top_;
        Cards::Card_data* second = top_->next;

        //std::cout << "second last card: " << secondLast->data << std::endl;

        // start moving cards
        // card next to last card is now 'first' i.e last card is now second last
        last->next = first;
        // first card is now last card, point 'next' nowhere
        first->next = nullptr;
        // second card is now first card
        top_ = second;


        return true;

    } else {
        return false;
    }
}

// Prints the content of the data structure with ordinal numbers
// to the output stream given as a parameter starting from the last element.
void Cards::print_from_bottom_to_top(std::ostream& s)
{
    if (top_ != nullptr) {
        int n = 0;
        s << n << ": " <<recursive_print_reverse(top_, s, n) << std::endl;
    }
}
