#include "square.hh"

Square::Square(int x, int y, bool hasMine, std::vector< std::vector< Square > >* board):
    x_(x), y_(y), adMines_(0), hasMine_(hasMine), hasFlag_(false), isOpened_(false), board_(board)     {

}

// Returns true if this square has a flag, else false.
bool Square::hasFlag() const
{
    return hasFlag_;
}

// Method that is called when player opens a square, returns true if this square has no mine, else false.
bool Square::open()
{
    if (hasMine_) {
        isOpened_ = true;
        return false;

    } else {
        // Using areaClear to handle revealing square(s)
        areaClear();

        return true;
    }
}

// Returns true if this square has a flag and a mine, false else.
bool Square::isReady() const
{
    if (hasMine_ and hasFlag_) {
        return true;

    } else if (not hasMine_){
        return true;

    } else {
        return false;
    }
}

// Reveals non-mine square(s): this square and in some cases all adjacent squares
void Square::areaClear() {

    // If this square has a flag, do nothing
    if (not hasFlag_) {

        // If this square has no adjacent mines, all adjacent squares (non-flag ones) are revealed.
        if (not isOpened_ and adMines_ == 0) {

            isOpened_ = true;
            // go through all adjacent squares and call this method on the ones that have no mine.
            for (unsigned int y = sizeVal(y_ - 1) ; y < sizeVal(y_ + 2) ; ++y) {

                for (unsigned int x = sizeVal(x_ - 1) ; x < sizeVal(x_ + 2) ; ++x) {

                    Square& square = board_->at(y).at(x);
                    if (not square.isOpened_) {
                        // recursion call
                        square.areaClear();
                    }
                }
            }
        } else {
            // In this case (mines adjacent to this square) only this square is revealed.
            isOpened_ = true;
        }
    }
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
    if (isOpened_) {
        if (hasMine_) {
            stream << "*";
        } else {
            stream << adMines_;
        }

    } else {
        if (hasFlag_) {
            stream << "P";
        } else {
            stream << ".";
        }
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
