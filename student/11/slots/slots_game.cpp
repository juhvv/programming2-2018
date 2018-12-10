#include "slots_game.hh"



SlotsGame::SlotsGame(QSlider *betSlider, QLCDNumber* moneyScr,
                     QPushButton* insertMoney, QPushButton* startGame):
    playerMoney_(0), curBet_(0.05),betSlider_(betSlider), moneyScr_(moneyScr)
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
        set_lcd();
        emit start_reels();
    }
}

// slot called when money is inserted
void SlotsGame::money_inserted()
{
    playerMoney_ += 0.10;
    set_lcd();
}

/* Slot called when all reels have stopped. Receives vector
 * containing names of fruits in middle row as parameter and calculates
 * possible winning sum.
*/
void SlotsGame::game_ended(const std::vector<std::string> results)
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
    // DELET
    std::cout << "---DEBUG START---" << std::endl;
    std::cout << "len: " << winMap.size() << std::endl;
    for (auto pair : winMap) {
        std::cout << pair.first << ":" << pair.second << std::endl;
    }

    int multiplier = 0;

    for (auto pair : winMap) {
        int curFruitAmount = pair.second;

        // get win conditions for this fruit
        auto winVec = WINMULT.at(pair.first);

        for (auto winCondPair : winVec) {
            if ( winCondPair.first == curFruitAmount) {
                // if one of the found win conditions matches result,
                // set 'multiplier' to that win condition's multiplier value
                std::cout << "win condition triggered" << std::endl; // DELET
                multiplier = winCondPair.second;
                //break;
            }
        }
    }

    if (multiplier != 0) {
        playerMoney_ += curBet_ * multiplier;
        std::cout << "Win: " << curBet_ * multiplier << std::endl;

    } else {
        std::cout << "No win." << std::endl;
    }
    set_lcd();

    // DELET
    std::cout << "---DEBUG END---" << std::endl;

}

// Sets lcd display to show current money.
void SlotsGame::set_lcd()
{
    int i = playerMoney_;
    // set printing format (00.00)
    moneyScr_->display(QString("%1").arg(i, 2, 10, QChar('0'))
                       + "."
                       + QString("%1").arg(qRound((playerMoney_ - i) * 100), 2, 10, QChar('0'))
                       + QString("%1").arg(i, 1, 10, QChar('0')));
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
