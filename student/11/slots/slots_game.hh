#ifndef SLOTS_GAME_HH
#define SLOTS_GAME_HH

#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QLCDNumber>

#include <iostream>

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

    private slots:
        void bet_changed();

};

#endif // SLOTS_GAME_HH
