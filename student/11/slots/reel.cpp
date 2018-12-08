/*
#####################################################################
# TIE-02207 Programming 2: Basics, F2018                            #
# Project4: Slots                                                   #
# Program description: Implements a virtual slots game.             #
# File: reel.cpp                                                    #
# Description: Draws random fruits for labels to display.           #
# Notes: * This is an exercise program.                             #
#        * Students need to modify this file.                       #
#####################################################################
*/

#include "reel.hh"


Reel::Reel(const std::vector<QLabel*>& labels,
           const QPushButton* lock_button,
           const Fruits* fruits,
           std::shared_ptr<std::default_random_engine> rng): first_(nullptr), last_(nullptr){

    // create looped list
    for (auto pair : *fruits) {
        Reel_data* newFruit = new Reel_data{pair.first, pair.second.first, first_, nullptr};
        first_ = newFruit;
        if (newFruit->next != nullptr) {
            newFruit->next->prev = newFruit;

        } else {
            last_ = newFruit;
        }
    }
    // link first and last element
    last_->next = first_;
    first_->prev = last_;

    printPtr_ = first_;

    lab1_ = labels[0];
    lab2_ = labels[1];
    lab3_ = labels[2];

    print_syms();

    // Connect all signals & slots you need here.
}

Reel::~Reel()
{
    // un-loop the list
    last_->next = nullptr;

    // delete elements
    while (first_ != nullptr) {
        Reel_data* reelToBeRemoved = first_;

        first_ = first_->next;
        delete reelToBeRemoved;
    }
}

// index the list forward by one
void Reel::test_index()
{
    first_ = first_->next;
    print_syms();
}

// sets display labels to correspond three consecutive elements of the list
void Reel::print_syms()
{
    lab2_->setPixmap(first_->img);
    lab1_->setPixmap(first_->prev->img);
    lab3_->setPixmap(first_->next->img);
}
