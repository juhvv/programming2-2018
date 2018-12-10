/*
 * TIE-02207 ,fall 2018
 * Slots project
 * Juho Viljamaa, 275354, viljamaa@student.tut.fi
 * Program description: Implements a virtual slots game.
 * file: slots_game.cpp
*/

#include "slots_game.hh"


SlotsGame::SlotsGame(QSlider *betSlider, QLCDNumber* moneyScr,
                     QLCDNumber* winLoseScr, QPushButton* insertMoney,
                     QPushButton* startGame):
    playerMoney_(0), curBet_(0.05),betSlider_(betSlider), moneyScr_(moneyScr), winLoseScr_(winLoseScr)
{
    set_lcd();

    // connect slots&signals
    connect(insertMoney, &QPushButton::clicked, this, &SlotsGame::money_inserted);
    connect(betSlider, &QSlider::valueChanged, this, &SlotsGame::bet_changed);
    connect(startGame, &QPushButton::clicked, this, &SlotsGame::game_started);
}

// slot called when start button is pressed
void SlotsGame::game_started()
{
    // start game only if player has enough money
    // comparing to a slightly reduced value to prevent unsignificant
    // diffirences from affecting result of comparison
    if (playerMoney_ >= (curBet_ - 0.00001)) {
        playerMoney_ -= curBet_;

        // make sure player money cant be negative, like '-0.000001' in this case.
        if (playerMoney_ < 0) {
            playerMoney_ = 0;
        }
        set_lcd();
        emit start_reels();
    }
}

// slot called when money is inserted
void SlotsGame::money_inserted()
{
    playerMoney_ += 0.10;
    totalInserted += 0.10;
    set_lcd();
}

/* Slot called when all reels have stopped. Receives vector
 * containing names of fruits in middle row as parameter and calculates
 * possible winning sum.
*/
void SlotsGame::spins_completed(const std::vector<std::string> results)
{
    // map that stores each fruit and amount
    std::map<std::string, int> winMap = {};

    for ( auto fruit : results ) {
        if (winMap.find(fruit) == winMap.end()) {
            winMap.insert( {fruit, 1} );

        } else {
            ++winMap.at(fruit);
        }
    }
    // vector to store possible win multipliers
    std::vector<int> winMultVec = {};

    for (auto pair : winMap) {
        int curFruitAmount = pair.second;

        // get win conditions for this fruit
        auto winVec = WINMULT.at(pair.first);

        for (auto winCondPair : winVec) {
            if ( winCondPair.first == curFruitAmount) {
                // if a win conditions matches result, insert that multiplier
                // to 'winMultVec'
                winMultVec.push_back(winCondPair.second);
            }
        }
    }

    if (winMultVec.size() != 0) {
        // set multiplier to largest value of 'winMultVec'
        int multiplier = *max_element(winMultVec.begin(), winMultVec.end());
        // calculate win sum
        playerMoney_ += curBet_ * multiplier;
        totalWon += curBet_ * multiplier;

        // Signal to disable lock buttons for next spin
        emit win_signal(true);

    }
    set_lcd();

}

// Sets lcd display to show current money.
void SlotsGame::set_lcd()
{
    // use printing format '.00'
    moneyScr_->display(QString("%1").arg(playerMoney_, 0, 'f', 2));

    double totalWinLost = totalWon - totalInserted;
    winLoseScr_->display(QString("%1").arg(totalWinLost, 0, 'f', 2));
}

// Slot called when bet slider's value changes; sets current bet
void SlotsGame::bet_changed()
{
    if (betSlider_->value() == 1) {
        curBet_ = 0.20;

    } else {
        curBet_ = 0.05;
    }
}
