#ifndef SLOTS_GAME_HH
#define SLOTS_GAME_HH

#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QLCDNumber>

#include <iostream>

// alias for map containing fruits and their win conditions and multipliers
using WinMultMap = std::map< std::string, std::vector< std::pair<int, int>> >;

/* Map with name of a fruit on the reels as key and vector containing pairs as
 * value. The pair contains "win condition" and corresponding "prize" for this fruit.
 * This is represented by two integers: First integer is the required amount of this
 * fruit on the middle line to win ("win condition"). Second integer is
 * win multiplier for this win situation. ("prize")
*/
const WinMultMap WINMULT{
    {"cherries", {{3,2}}},
    {"strawberry", {{2,2}, {3,5}}},
    {"orange", {{2,2}, {3,5}}},
    {"pear", {{1,2}, {3,5}}},
    {"apple", {{3,10}}},
    {"bananas", {{3,10}}},
    {"tomato", {{3,10}}},
    {"grapes", {{3,100}}},
    {"eggplant", {{3,100}}}
};

/// \class SlotsGame
/// \brief Implements game logic and rules.
///
///
class SlotsGame: public QObject {
    Q_OBJECT

    public:
        /// \brief Construct a new SlotsGame object.
        ///
        /// \param[in] betSlider Slider which determines current bet.
        /// \param[in] moneyScr QLCDNumber object which displays current funds.
        /// \param[in] insertMoney Button used to insert fixed amount of money.
        /// \param[in] startGame Button used to start tha game.
        ///
        SlotsGame(QSlider* betSlider, QLCDNumber* moneyScr,
                  QPushButton* insertMoney, QPushButton* startGame);

    public slots:
        void game_started();
        void money_inserted();
        void game_ended(const std::vector<std::string> results);

    signals:
        void start_reels();

    private:
        double playerMoney_;
        double curBet_;

        QSlider* betSlider_;
        QLCDNumber* moneyScr_;

        void set_lcd();
        void calculate_win();

    private slots:
        void bet_changed();

};

#endif // SLOTS_GAME_HH
