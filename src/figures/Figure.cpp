#include <sstream>
#include "Figure.hpp"
#include "../rules/Check.hpp"

/**
 * function returns true if a movement will cause check
 * @param king king on which check can be done
 * @param board we need to know the state of the board
 * @param numPosBefore numerical position before movement
 * @param letPosBefore letter position before movement
 * @param numPosAfter numerical position after movement
 * @param letPosAfter letter position atfer movement
 * @return
 */
bool Figure::checkCastlingAfterMovement(King * king, Board * board,
                                const int & numPosBefore, const int & letPosBefore,
                                const int & numPosAfter, const int & letPosAfter) {

    //we have to store temporarily figures from the field where the figure is standing before the current movement
    //and where it can stand after such movement
    Figure * tmpFigureBefore = board->getFigureAtPos(numPosBefore, letPosBefore);
    Figure * tmpFigureAfter = board->getFigureAtPos(numPosAfter, letPosAfter);

    //reset those fields
    board->putFigure(nullptr, numPosBefore, letPosBefore);
    board->putFigure(nullptr, numPosAfter, letPosAfter);

    //temporarily move figure to a new place
    board->putFigure(tmpFigureBefore, numPosAfter, letPosAfter);

    //now we have imitation of how the board might look after such movement and we can check if such position cause the check
    Check * check = new Check(board, king);

    //store and return result
    bool result;
    //check the check
    result = check->check();
    delete check;

    //restore the board as it was before calling this function
    board->putFigure(tmpFigureBefore, numPosBefore, letPosBefore);
    board->putFigure(tmpFigureAfter, numPosAfter, letPosAfter);

    return result;
}

/**
 * move figure to field with given coordinates
 * @param board we have to update board after movement
 * @param numPos numerical position after movement
 * @param letPos letter position after movement
 */
void Figure::move(Board * board, const int & numPos, const int & letPos) {
    if (numPos < 0 || numPos > (int)(BOARD_SIZE-1) || letPos < 0 || letPos >  (int)(BOARD_SIZE-1)) throw InvalidPosition();
    ++m_moves;
    m_numPos = numPos;
    m_letPos = letPos;
    board->putFigure(this, numPos, letPos);
}

/**
 * overloaded operator << for printing a figure
 * @param os
 * @param figure
 * @return
 */
ostream & operator << (ostream & os, const Figure & figure) {
    os <<  figure.getFigColor() << figure.getFigType();
    return os;
}

/*
string Figure::print() const {
    ostringstream os;
    os << m_figColor << m_figType;
    return os.str();
}
 */