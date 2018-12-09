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
           std::shared_ptr<std::default_random_engine> rng):
    spinTimer_(new QTimer(this)), first_(nullptr), last_(nullptr), reelRng_(rng)
{
    fruitVec_ = {};
    // create 'Reel_data' elements and store pointers to 'fruitVec_'
    for (auto pair : *fruits) {
        Reel_data* newFruit = new Reel_data{pair.first,
                pair.second.first, pair.second.second ,first_, nullptr};
        fruitVec_.push_back(newFruit);
    }

    // randomize order of fruits in this reel
    shuffle (fruitVec_.begin(), fruitVec_.end(), *reelRng_);
    setup_reel();

    // set display labels
    lab1_ = labels[0];
    lab2_ = labels[1];
    lab3_ = labels[2];

    lockButton_ = lock_button;
    print_fruits();

    indexCounter_ = 0;

    // Connect all signals & slots
    connect(spinTimer_, &QTimer::timeout, this, &Reel::index_reel);
    connect(spinTimer_, &QTimer::timeout, this, &Reel::stop_reel);
}

// destructor
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

    delete spinTimer_;
}

// Slot called when signal to spin this reel is emitted
void Reel::spin()
{
    if (not lockButton_->isChecked()) {
        spinTimer_->start(50);
    } else {
        emit stopped(first_->id);
    }

}

// Index the list forward by one
void Reel::index_reel()
{
    first_ = first_->next;
    ++indexCounter_;
    print_fruits();
}

/*
 * Slot that checks if reel should stop. Also randomizes
 * the fruit
*/
void Reel::stop_reel()
{
    // the reel should index at least 40 times
    if ((indexCounter_ > 40)) {

        // randomize index of fruit to stop at
        int result = fruitFrqDist_(*reelRng_);
        /* reel should stop only if the randomized fruit is the same that is
         *  currently showed in the middle label (= target of 'first_')
         * if not, reel keeps spinning until such case is encountered;
         * this creates random spin time for reel
        */
        if (first_->id == fruitVec_.at(result)->id) {
            spinTimer_->stop();
            emit stopped(first_->id);
            indexCounter_ = 0;
        }
    }
}
/*
 * Method for setting up reel. Links structs in 'fruitVec_' together and creates
 * distribution based on frequencies in 'Reel_data' structs.
*/
void Reel::setup_reel()
{
    // vector for frequencies (weights)
    std::vector<int> weightVec = {};
    const int vecLen = fruitVec_.size();

    for (int n = 0; n < vecLen; ++n) {
        auto elem = fruitVec_.at(n);
        weightVec.push_back(elem->freq);

        // link elements
        if (n == 0) {
            first_ = elem;
            // link first element to last element
            elem->prev = fruitVec_.at(vecLen - 1);
            elem->next = fruitVec_.at(n + 1);

        } else if (n == vecLen - 1) {
            last_ = elem;
            elem->prev = fruitVec_.at(n - 1);
            // link last element to first element
            elem->next = *fruitVec_.begin();

        } else {
            elem->prev = fruitVec_.at(n - 1);
            elem->next = fruitVec_.at(n + 1);
        }
    }
    // create distibution
    std::discrete_distribution<> dist(weightVec.begin(), weightVec.end());
    fruitFrqDist_ = dist;
}


// sets display labels to correspond three consecutive elements of the list
void Reel::print_fruits() const
{
    lab2_->setPixmap(first_->img);
    lab1_->setPixmap(first_->prev->img);
    lab3_->setPixmap(first_->next->img);
}
