#ifndef SQUARE_HH
#define SQUARE_HH

#include <vector>
#include <iostream>


class Square
{
public:
    // Constructor
    Square (int x, int y, bool hasMine, std::vector< std::vector< Square > >* board);

    // Public methods
    bool hasFlag() const;
    bool open();
    bool isReady() const;
    void print(std::ostream& stream) const;

    void removeFlag();
    void addFlag();
    void countAdjacent();

private:
    // Private variables
    int x_;
    int y_;
    int adMines_;

    bool hasMine_;
    bool hasFlag_;
    bool isOpened_;

    std::vector< std::vector< Square > >* board_;

    // Private methods
    unsigned int sizeVal(int size_int);
    void areaClear();
};

#endif // SQUARE_HH
