#include <iostream>
#include <memory>
#include <algorithm>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    // check if list is empty
    if (top_ == nullptr) {
        return false;

    } else {
        // create second pointer that points to first element of list (this case: element to be removed)
        std::shared_ptr<Card_data> cardToBeRemoved = top_;
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

        return true;
    }
}

void Cards::reverse()
{

}

std::shared_ptr<Cards::Card_data> Cards::getBottomCard( std::shared_ptr<Card_data> curCard )
{
    if (curCard->next == nullptr) {
        return curCard;
    } else {
        return getBottomCard(curCard);
    }
}

// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file reverse.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in reverse.cpp
