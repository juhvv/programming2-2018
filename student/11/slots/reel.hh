/*
#####################################################################
# TIE-02207 Programming 2: Basics, F2018                            #
# Project4: Slots                                                   #
# Program description: Implements a virtual slots game.             #
# File: reel.h                                                      #
# Description: Draws random fruits for labels to display.           #
# Notes: * This is an exercise program.                             #
#        * Students need to modify this file.                       #
#####################################################################
*/

#ifndef SLOTS_REEL_H
#define SLOTS_REEL_H

#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <map>
#include <memory>
#include <algorithm>
#include <random>
#include <string>
#include <utility>
#include <vector>

// Fruits is an alias for a map which contains a fruit's name and
// corresponding image and likelyhood of appearance.
using Fruits = std::map<std::string, std::pair<QPixmap, int>>;

/// \class Reel
/// \brief Implements reels which are used to determine if the player has won.
///
/// Reel spins for a random duration and draws random fruits to display on its
/// labels. Reel signals MainWindow with the name of the middlemost fruit, but
/// an ordered (top-to-bottom) list of all fruits can also be queried.
///
class Reel: public QObject {
    Q_OBJECT

public:

    /// \brief Construct a new Reel.
    ///
    /// \param[in] labels Labels which should be used to display the symbols.
    /// \param[in] lock_button Button whose state determines if Reel is locked.
    /// \param[in] fruits Images and frequencies of each fruit.
    /// \param[in] rng Random number generator used to determine the symbols.
    ///
    Reel(const std::vector<QLabel*>& labels,
         const QPushButton* lock_button,
         const Fruits* fruits,
         std::shared_ptr<std::default_random_engine> rng);

    // Dynamic data structure must have a destructor
    // that can be called to deallocate memory,
    // when the data structure is not needed any more.
    ~Reel();

public slots:
    void spin();

signals:

    /// \brief Is emitted when the Reel stops.
    ///
    /// \param[in] Name of the middle symbol on the Reel.
    ///
    void stopped(const std::string& middleSym);

private:
    // struct for each fruit on reel
    struct Reel_data {
        std::string id;
        QPixmap img;
        int freq;
        Reel_data* next;
        Reel_data* prev;
    };
    // container for 'Reel_data' pointers
    std::vector<Reel_data*> fruitVec_;

    // pointers to first and last element of list
    Reel_data* first_;
    Reel_data* last_;

    // timer used to spin the reels
    QTimer* spinTimer_;

    // distribution and random engine variables
    std::shared_ptr<std::default_random_engine> reelRng_;
    std::discrete_distribution<int> fruitFrqDist_;

    // displays fruits on labels
    void print_fruits() const;
    // method for linking 'Reel_data' elements and other stuff
    void setup_reel();


    // labels which are used by this reel
    QLabel* lab1_;
    QLabel* lab2_;
    QLabel* lab3_;

    // pointer to reel's lock button
    const QPushButton* lockButton_;

    // counter for tracking how long reel spins
    int indexCounter_;

    private slots:
        void index_reel();
        void stop_reel();

};  // class Reel


#endif  // SLOTS_REEL_H
