#ifndef SQUARE_HH
#define SQUARE_HH

#include <vector>
#include <iostream>


class Square
{
public:
    Square (int x, int y, bool hasMine, std::vector< std::vector< Square > >* board);
    bool hasFlag() const;
    //delet this
    bool hasMine() const;

    bool open() const;
    bool isReady() const;
    void print(std::ostream& stream) const;

    void removeFlag();
    void addFlag();
    void countAdjacent();

private:
    int x_;
    int y_;
    int adMines_;

    bool hasMine_;
    bool hasFlag_;

    std::vector< std::vector< Square > >* board_;

};

#endif // SQUARE_HH
