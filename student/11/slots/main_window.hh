/*
#####################################################################
# TIE-02207 Programming 2: Basics, F2018                            #
# Project4: Slots                                                   #
# Program description: Implements a virtual slots game.             #
# File: main_window.h                                               #
# Description: Implements a UI for the game to be playable.         #
# Notes: * This is an exercise program.                             #
#        * Students need to modify this file.                       #
#####################################################################
*/

#ifndef SLOTS_MAINWINDOW_H
#define SLOTS_MAINWINDOW_H

#include "reel.hh"
#include "slots_game.hh"
#include "ui_main_window.h"
#include <QMainWindow>
#include <string>


/// \class MainWindow
/// \brief Implements the main window which is used to interact with the game.
///
/// MainWindow owns all the widgets used to display the game to the player
/// and to play the game. MainWindow contains the whole game, no other windows
/// are used.
///
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /// \brief Construct a new MainWindow.
    ///
    /// \param[in] parent Points to this MainWindow's parent widget.
    ///
    explicit MainWindow(QWidget* parent = nullptr);

signals:
    /// \brief Emitted when round is over.
    ///
    /// \param[in] Vector containing names of fruits on middle line.
    void spins_results(const std::vector<std::string> result);

private slots:

    /// \brief Check if the round is over and prepare for the next round.
    ///
    /// Should get called when a Reel has decided on which fruits to display.
    /// When this slot is called three times in a round, the round ends
    /// and names of fruits are passed forwards.
    ///
    /// \param[in] middle_sym Name of the fruit symbol on the middle lane.
    ///
    void reelStopped(const std::string& midSymId);

    /// \brief Spins the reels
    ///
    void spin_reel();

    /// \brief Disables/enables ui buttons.
    ///
    void set_button_state(bool value);

    /// \brief Sets reels' lock buttons to desired state
    /// \param[in] value Value to set buttons to.
    ///
    void toggle_lock_btns(bool value = false);


private:

    /// \brief Initialize the Reels, buttons, etc. so the game can be played.
    ///
    void initUi();

    const Fruits fruits_;       ///< The game symbols and their rarities.
    Ui::MainWindowClass ui_;    ///< (Black) Qt magic handling the UI.
    std::vector<Reel*> reels_;  ///< Container for pointers to reels.
    std::vector<std::string> resultVec_; ///< Container for results from spins

    /// \brief Container for pointers to reel locking buttons
    std::vector<QPushButton*> reelLockBtns_;

    SlotsGame* game_core_; ///< Object for running the game

};  // class MainWindow


#endif  // SLOTS_MAINWINDOW_H
