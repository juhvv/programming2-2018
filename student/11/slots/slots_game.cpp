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
    if (playerMoney_ >= (curBet_ - 0.00001)) {
        playerMoney_ -= curBet_;
        set_lcd();
        emit start_reels();

    } else {

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
    // delet this
    std::cout << "---DEBUG START---" << std::endl;
    for (int n = 0; n < results.size(); ++n) {
        std::cout << n << ": " << results.at(n) << std::endl;
    }
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
