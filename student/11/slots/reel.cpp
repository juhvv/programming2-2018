/*
 * TIE-02207 ,fall 2018
 * Slots project
 * Juho Viljamaa, 275354, viljamaa@student.tut.fi
 * Program description: Implements a virtual slots game.
 * file: reel.cpp
*/

#include "reel.hh"


Reel::Reel(const std::vector<QLabel*>& labels,
           const QPushButton* lock_button,
           const Fruits* fruits,
           std::shared_ptr<std::default_random_engine> rng,
           const int delay):
                first_(nullptr),
                last_(nullptr),
                spinTimer_(new QTimer(this)),
                spinDelay_(delay),
                reelRng_(rng)
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

// Destructor
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

// Slot called when signal to spin this reel is received
void Reel::spin()
{
    // check if reel is locked
    if (not lockButton_->isChecked()) {
        // randomize index of fruit to stop at
        resultIndex_ = fruitFrqDist_(*reelRng_);

        // randomize spin time
        std::uniform_int_distribution<int> spinDist(0,8);
        spinTime_ = 25 + spinDelay_ + spinDist(*reelRng_);

        // start timer
        spinTimer_->start(50);
    } else {
        emit stopped(first_->id);
    }
}

// Switch pointer 'first_' to next element on the list.
// -> The reel indexes forward by one.
void Reel::index_reel()
{
    first_ = first_->next;
    ++indexCounter_;
    print_fruits();
}

/*
 * Slot that checks if reel should stop. When reel stops,
 *  stopped signal is emitted.
*/
void Reel::stop_reel()
{
    // check if reel has spun long enough
    if ((indexCounter_ > spinTime_)) {

        // keep spinning the reel until result fruit is in the middle
        if (first_->id == fruitVec_.at(resultIndex_)->id) {
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
    const int fruitVecLen = fruitVec_.size();

    // link elements and get their frequencies
    for (int n = 0; n < fruitVecLen; ++n) {
        // get 'Reel_data' element pointer
        auto elem = fruitVec_.at(n);
        weightVec.push_back(elem->freq);

        // link elements
        if (n == 0) {
            first_ = elem;
            // link first element to last element
            elem->prev = fruitVec_.at(fruitVecLen - 1);
            elem->next = fruitVec_.at(n + 1);

        } else if (n == fruitVecLen - 1) {
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
    lab1_->setPixmap(first_->next->img);
    lab3_->setPixmap(first_->prev->img);
}
