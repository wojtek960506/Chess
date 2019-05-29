#include "Move.hpp"

/**
 * function checks if the field where we want to move if available for current figure in the current state
 * @return true in case of such possibility; false otherwise
 */
bool Move::checkPossibilityToMove() {
    for (const auto & fieldToMove : m_fieldsToMove) {
        if (fieldToMove.getNumPos() == m_numPos && fieldToMove.getLetPos() == m_letPos) {
            m_moveType = fieldToMove.getMoveType();
            return true;
        }
    }
    return false;
}

/**
 * function to move figure on the selected field (just a normal move - i.e. no special rule is applied)
 */
void Move::doNormalMove() {
    int numPos = m_figure->getNumPos();
    int letPos = m_figure->getLetPos();
    m_figure->move(m_board, m_numPos, m_letPos);
    m_board->resetPtrAtPos(numPos, letPos);
}

/**
 * function to delete figure when it was captured
 * @param numPos - numeric position of this figure
 * @param letPos - letter position of this figure
 */
void Move::deleteFigure(const int & numPos, const int & letPos) {
    Figure * figure = m_board->getFigureAtPos(numPos, letPos);
    auto it = m_figuresPtr->find(figure);
    m_figuresPtr->erase(it);
    delete figure;
    m_board->resetPtrAtPos(numPos, letPos);
}

/**
 * function to move figure on the field where there is standing figure of opposite color (different then king)
 */
void Move::doCapture() {
    //first delete figure to capture
    deleteFigure(m_numPos, m_letPos);
    /*
    Figure * figure = m_board->getFigureAtPos(m_numPos, m_letPos);
    auto it = m_figuresPtr->find(figure);
    m_figuresPtr->erase(it);
    delete figure;
    */

     //then move figure
    doNormalMove();
}

/**
 * function to execute the spacial king move - castling; actually we also change position of the rook involved in this castling
 */
void Move::doCastling() {
    //first move king as it is actually figure which makes this move
    int kingNumPos = m_figure->getNumPos();
    int kingLetPos = m_figure->getLetPos();
    m_figure->move(m_board, m_numPos, m_letPos);
    m_board->resetPtrAtPos(kingNumPos, kingLetPos);
    //then move rook to complete the castling
    int rookNumPos = kingNumPos, oldRookLetPos, newRookLetPos; //rook is on the same rank as king after castling
    if (m_letPos > LetterPosition::LET_POS_E) { //right side castling
        oldRookLetPos = LetterPosition::LET_POS_H;
        newRookLetPos = LetterPosition::LET_POS_F;
    } else { //left side castling
        oldRookLetPos = LetterPosition::LET_POS_A;
        newRookLetPos = LetterPosition::LET_POS_D;
    }
    Figure * figure = m_board->getFigureAtPos(rookNumPos, oldRookLetPos);
    figure->move(m_board, rookNumPos, newRookLetPos);
    m_board->resetPtrAtPos(rookNumPos, oldRookLetPos);
}

/**
 * function to execute the special capture of the pawn by a pawn - en passant;
 * pawn is captured by another pawn and after it attacking pawn is on the different position then its opponent
 */
void Move::doEnPassant() {
    //first delete the pawn to capture with en passant
    //captured pawn is on the same rank as offensive pawn before movement and on the same file as offensive pawn after movement
    int captNumPos = m_figure->getNumPos();
    int captLetPos = m_letPos;
    deleteFigure(captNumPos, captLetPos);
    /*
    Figure * figure = m_board->getFigureAtPos(captNumPos, captLetPos);
    auto it = m_figuresPtr->find(figure);
    m_figuresPtr->erase(it);
    delete figure;
    */
    //move offensive pawn
    doNormalMove();
}

/**
 * function to check if the move to selected field is possible. In case of such possibility the move is executed.
 * @return true in case of possibility to move; false otherwise
 */
bool Move::check() {
    if (!checkPossibilityToMove()) return false;
    switch (m_moveType) {
        case MoveType::NORMAL:
            doNormalMove();
            break;
        case MoveType::CAPTURE:
            doCapture();
            break;
        case MoveType::EN_PASSANT:
            doEnPassant();
            break;
        case MoveType::CASTLE:
            doCastling();
            break;
        default:
            return false;
    }
    return true;
}
