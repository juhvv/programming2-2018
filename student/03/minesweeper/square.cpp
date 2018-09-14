#include "square.hh"

Square::Square(int x, int y, bool hasMine, std::vector< std::vector< Square > >* board):
    x_(x), y_(y), adMines_(0), hasMine_(hasMine), hasFlag_(false), board_(board)     {

}

bool Square::hasFlag() const
{
    return hasFlag_;
}
// delet this, do not change
bool Square::hasMine() const
{
    return hasMine_;
}


bool Square::open() const
{
    return false;
}

bool Square::isReady() const
{
    return false;
}

// Returns int values from 0 to the size of board, paramteter values out of this range are changed to edge values of this range.
unsigned int Square::sizeVal(int size_int) {

    int board_size = board_->size();
    if (size_int < 0) {
        return 0;

    } else if (size_int > board_size) {
        return board_size;

    } else {
        return size_int;
    }
}

// Determines output mark of this square to parameter stream.
void Square::print(std::ostream& stream) const
{
    if (hasFlag_) {
        stream << "P";

    } else if (hasMine_) {
        stream << ".";

    } else {
        stream << adMines_;
    }
}

// Removes flag from this square.
void Square::removeFlag()
{
    hasFlag_ = false;
}

// Adds flag to this square.
void Square::addFlag()
{
    hasFlag_ = true;
}

// Counts how many mines are there in squares adjacent to this square.
void Square::countAdjacent()
{
    // using sizeVal to prevent index errors
    for (unsigned int y = sizeVal(y_ - 1) ; y < sizeVal(y_ + 2) ; ++y) {

        for (unsigned int x = sizeVal(x_ - 1) ; x < sizeVal(x_ + 2) ; ++x) {

            Square square = board_->at(y).at(x);
            if (square.hasMine_) {
                adMines_ += 1;
            }
        }
    }
}
