#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>


class Player
{
public:
    Player(std::string name);
    std::string get_name() const;
    int get_points() const;
    bool has_won() const;

    void add_points(int pts);

private:
    std::string name_;
    int points_;
};

#endif // PLAYER_HH
