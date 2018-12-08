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

    for (auto pair : *fruits) {
        Reel_data* newFruit = new Reel_data{pair.first, pair.second.first, first_, nullptr};
        first_ = newFruit;
        if (newFruit->next != nullptr) {
            newFruit->next->prev = newFruit;

        } else {
            last_ = newFruit;
        }
    }
    last_->next = first_;
    first_->prev = last_;

    // Connect all signals & slots you need here.
}
