/*
#####################################################################
# TIE-02207 Programming 2: Basics, F2018                            #
# Project4: Slots                                                   #
# Program description: Implements a virtual slots game.             #
# File: main_window.cpp                                             #
# Description: Implements a UI for the game to be playable.         #
# Notes: * This is an exercise program.                             #
#        * Students need to modify this file.                       #
#####################################################################
*/

#include "main_window.hh"
#include <QPixmap>
#include <QString>
#include <chrono>
#include <map>
#include <memory>
#include <random>
#include <utility>

#include <iostream>


// To avoid polluting the global namespace with all kinds of
// names, free functions and global variables / constants are
// usually placed inside a namespace. As we don't have a named
// namespace here, we'll use the anonymous namespace instead.
namespace {

/// \brief Get the fruit symbols and their frequencies.
///
/// \return A map of image names and corresponding images and frequencies.
///
Fruits loadFruits() {
    // Set frequencies for each symbol.
    // * You can freely play around with the values below.
    // * Values are relative to each other, higher == more common.
    // * Names of these fruits (and berries too) have to actually match
    //   images found on the disk. The images must be in the PNG format.
    const std::map<std::string, int> frequencies{
        {"cherries", 56},
        {"strawberry", 50},
        {"orange", 46},
        {"pear", 39},
        {"apple", 35},
        {"bananas", 30},
        {"tomato", 24},
        {"grapes", 15},
        {"eggplant", 5}
    };

    // Define where the images can be found and what kind of images they are.
    // * Here we assume that the build directory is next to Slots directory.
    const std::string directory("../slots/Resources/");
    const std::string extension(".png");

    // Load the images into QPixmaps and bundle them with their frequencies.
    Fruits symbols;
    for (const std::pair<std::string, int>& frequency : frequencies) {
        const std::string filename = directory + frequency.first + extension;
        const QPixmap image(QString::fromStdString(filename));
        symbols[frequency.first] = std::make_pair(image, frequency.second);
    }

    return symbols;
}

}  // namespace


MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    fruits_(loadFruits()){

    ui_.setupUi(this);
    initUi();
    resultVec_ = {};
}

// Receives name of middle fruit from reels and emits it to 'SlotsGame' object
void MainWindow::reelStopped(const std::string& middle_sym) {
    resultVec_.push_back(middle_sym);

    // if 'resultVec_' has 3 elements, all reels have stopped
    if (resultVec_.size() == 3) {
        set_button_state(false);
        toggle_lock_btns();
        emit spins_results(resultVec_);

        resultVec_.clear();
    }
}

// Sets all reels to spin
void MainWindow::spin_reel()
{
    // lock buttons
    set_button_state(true);

    for (auto reel : reels_) {
        reel->spin();
    }
}

void MainWindow::initUi() {
    // Initialize and display current funds etc.

    // Set lock buttons to desired starting state.

    // Create one random number generator for all Reels to use.
    // * The seed value is obtained via the chrono library and
    //   represents the number of seconds since 1.1.1970.
    // * If you need to debug some pesky error, you can temporarily
    //   replace the seed with some literal. See Minesweeper or
    //   Waterdropgame versions 1 and 2.
    const auto time = std::chrono::high_resolution_clock::now();
    const auto seed = time.time_since_epoch().count();
    auto rng = std::make_shared<std::default_random_engine>(seed);

    // create game manager
    game_core_ = new SlotsGame(ui_.bet_slider, ui_.money_scr,
                               ui_.money_insert_btn, ui_.btn_start);

    // display labels for each reel
    const std::vector<QLabel*> labelVec1 = {ui_.reel1_lab1,
                                            ui_.reel1_lab2, ui_.reel1_lab3};
    const std::vector<QLabel*> labelVec2 = {ui_.reel2_lab1,
                                            ui_.reel2_lab2, ui_.reel2_lab3};
    const std::vector<QLabel*> labelVec3 = {ui_.reel3_lab1,
                                            ui_.reel3_lab2, ui_.reel3_lab3};

    // create reels and store their pointers/lock buttons
    Reel* reel1 = new Reel(labelVec1, ui_.lock1_btn, &fruits_, rng, 0);
    Reel* reel2 = new Reel(labelVec2, ui_.lock2_btn, &fruits_, rng, 16);
    Reel* reel3 = new Reel(labelVec3, ui_.lock3_btn, &fruits_, rng, 32);
    reels_ = {reel1, reel2, reel3};

    reelLockBtns_ = {ui_.lock1_btn, ui_.lock2_btn, ui_.lock3_btn};

    // connect slots&signals
    connect(reel1, &Reel::stopped, this, &MainWindow::reelStopped);
    connect(reel2, &Reel::stopped, this, &MainWindow::reelStopped);
    connect(reel3, &Reel::stopped, this, &MainWindow::reelStopped);

    connect(game_core_, &SlotsGame::start_reels, this, &MainWindow::spin_reel);
    connect(game_core_, &SlotsGame::win_signal, this, &MainWindow::toggle_lock_btns);
    connect(this, &MainWindow::spins_results, game_core_, &SlotsGame::spins_completed);
}

// Sets interactive ui elements' disabled state to 'value'
void MainWindow::set_button_state(bool value)
{
    ui_.lock1_btn->setDisabled(value);
    ui_.lock2_btn->setDisabled(value);
    ui_.lock3_btn->setDisabled(value);
    ui_.btn_start->setDisabled(value);
    ui_.bet_slider->setDisabled(value);
    ui_.money_insert_btn->setDisabled(value);
}

// Manages lock buttons, 'value = false' by default
void MainWindow::toggle_lock_btns(bool value)
{
    // buttons wont be disabled by default

    // determine whether buttons should be locked
    for (auto buttonPtr : reelLockBtns_) {
        // if a lock button is checked, lock buttons will be disabled
        if (buttonPtr->isChecked()) {
            value = true;
        }
    }

    // un-check buttons and set disable to current value of lockBtnIsDisabled
    for(auto buttonPtr : reelLockBtns_) {
        buttonPtr->setDisabled(value);
        buttonPtr->setChecked(false);
    }
}
