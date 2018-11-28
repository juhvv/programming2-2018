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
    fruits_(loadFruits()) {

    ui_.setupUi(this);
    initUi();
}

void MainWindow::reelStopped(const std::string& middle_sym) {

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

    // Create each Reel with its own specific labels, etc.
    // * Create the Reels yourself, nullptr is just a dummy value here.
    Reel* reel = nullptr;
    connect(reel, &Reel::stopped, this, &MainWindow::reelStopped);
}
