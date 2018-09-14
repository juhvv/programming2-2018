#include "square.hh"

Square::Square(int x, int y, bool hasMine, std::vector< std::vector< Square > >* board):
    x_(x), y_(y), adMines_(0), hasMine_(hasMine), hasFlag_(false), board_(board)     {

}

bool Square::hasFlag() const
{
    return false;
}
// delet this
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

void Square::print(std::ostream& stream) const
{
    if (hasMine_) {
        stream << ".";

    } else if (hasFlag_) {
        stream << "P";

    } else {
        stream << adMines_;
    }
}

void Square::removeFlag()
{

}

void Square::addFlag()
{

}

void Square::countAdjacent()
{
    for (unsigned int y = sizeVal(y_ - 1) ; y < sizeVal(y_ + 2) ; ++y) {

        for (unsigned int x = sizeVal(x_ - 1) ; x < sizeVal(x_ + 2) ; ++x) {
            Square square = board_->at(y).at(x);
            if (square.hasMine_) {
                adMines_ += 1;
            }
        }
    }
}
