#include "square.hh"

Square::Square(int x, int y, bool hasMine, std::vector< std::vector< Square > >* board):
    x_(x), y_(y), hasMine_(hasMine), hasFlag_(false), board_(board)     {

}

bool Square::hasFlag() const
{
    return false;
}

bool Square::open() const
{
    return false;
}

bool Square::isReady() const
{
    return false;
}

void Square::print(std::ostream& stream) const
{

}

void Square::removeFlag()
{

}

void Square::addFlag()
{

}

void Square::countAdjacent()
{

}
