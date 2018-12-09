#ifndef SLOTS_GAME_HH
#define SLOTS_GAME_HH

#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QLCDNumber>

/// \class SlotsGame
/// \brief Implements game logic and rules.
///
///
class SlotsGame: public QObject {
    Q_OBJECT

    public:
        SlotsGame(QSlider* betSlider, QLCDNumber* moneyScr,
                  QPushButton* insertMoney, QPushButton* startGame);

    public slots:
        void game_started();
        void money_inserted();

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
