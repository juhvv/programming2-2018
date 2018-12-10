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
    {"strawberry", {{3,2}}},
    {"orange", {{2,2}, {3,5}}},
    {"pear", {{2,2}, {3,5}}},
    {"apple", {{3,10}}},
    {"bananas", {{3,10}}},
    {"tomato", {{3,10}, {2,5}}},
    {"grapes", {{3,100}, {2,10}, {1,2}}},
    {"eggplant", {{3,100}, {2,10}, {1,5}}}
};

/// \class SlotsGame
/// \brief Implements game logic and rules.
///
/// Keeps track of the players money, calculates possible winnings and determines
/// some cases when reels cannot be locked.
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
        /// \brief Slot called when all reels have stopped.
        ///
        /// \param[in] results Vector with names of fruits on middle row.
        ///
        void spins_completed(const std::vector<std::string> results);


    signals:
        /// \brief Signal emitted when reels should start to spin.
        ///
        void start_reels();

        /// \brief Signal emitted when win occurs.
        /// Used to disable reel lock buttons.
        ///
        /// \param[in] value 'true' disables reel lock buttons.
        void win_signal(bool value);

    private:
        double playerMoney_;    ///< Players current money.
        double curBet_;         ///< Current bet.

        QSlider* betSlider_;    ///< Slider that determines current bet
        QLCDNumber* moneyScr_;  ///< Screen where current funds are dispalyed

        /// \brief Updates the display to show current money
        ///
        void set_lcd();

    private slots:
        /// \brief Updates current bet based on position of 'betSlider_'
        ///
        void bet_changed();

        /// \brief Starts the game if player has enough money.
        ///
        void game_started();

        /// \brief Increases player's money by 0.10 $ when called
        ///
        void money_inserted();
};

#endif // SLOTS_GAME_HH
