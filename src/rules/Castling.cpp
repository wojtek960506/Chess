#include "Castling.hpp"
#include "Check.hpp"
#include "CheckAttacksOnField.hpp"

/**
 * function to check if the king hasn't made any move yet
 * @return true in case of 0 moves of king; false in case of more moves of king
 */
bool Castling::checkKing() const {
    return m_king->getMoves() == 0;
}

/**
 * function to check if the rook hansn't made any move yet
 * @param numPos - numeric position of the rook
 * @param letPos - letter position of the rook
 * @return true in case of 0 moves of the given rook ; false in case of figure which is not rook or more than 0 moves
 */
bool Castling::checkRook(const int & numPos, const int & letPos) const {
    Figure *figure = m_board->getFigureAtPos(numPos, letPos);
    return !(figure == nullptr || figure->getFigType() != FigureType::ROOK
                || figure->getFigColor() != m_king->getFigColor() || figure->getMoves() > 0);
}

/**
 * function to check if the rook on the given side hasn't made any move yet
 * @return true in case of 0 moves of the given rook ; false in case of failure while checking the rook
 */
bool Castling::checkRooks() const {
    if (m_castlingSide == CastlingSide::CASTLING_LEFT) {
        if (m_king->getFigColor() == FigureColor::WHITE)
            return checkRook(NumericPosition::NUM_POS_1, LetterPosition::LET_POS_A);
        else //m_king->getFigColor() == FigureColor::BLACK
            return checkRook(NumericPosition::NUM_POS_8, LetterPosition::LET_POS_A);
    } else { //m_castlingSide == CastlingSide::CASTLING_RIGHT
        if (m_king->getFigColor() == FigureColor::WHITE)
            return checkRook(NumericPosition::NUM_POS_1, LetterPosition::LET_POS_H);
        else //m_king->getFigColor() == FigureColor::BLACK
            return checkRook(NumericPosition::NUM_POS_8, LetterPosition::LET_POS_H);
    }
}

/**
 * function to check if the king is check in te current state
 * @return true if the king is checked; false otherwise
 */
bool Castling::checkCheck() const {
    Check check(m_board, m_king);
    return check.check();
}

//returns true when fields between king and rook are free and those fields are not attacked by the figure of different color
/**
 * function to check if the fields between king and the rook are free
 * and if those fields are not attacked by any of the opponent's figures
 * @return true in case of no such figure; false otherwise
 */
bool Castling::checkFieldsBetweenKingAndRook() {
    int numPos;
    if (m_king->getFigColor() == FigureColor::WHITE) numPos = NumericPosition::NUM_POS_1;
    else numPos  = NumericPosition::NUM_POS_8;

    vector<int> letPositions;
    if (m_castlingSide == CastlingSide::CASTLING_LEFT) {
        //first we have to check if the fields between rook and king are empty
        if (m_board->getFigureAtPos(numPos,LetterPosition::LET_POS_B) != nullptr) return false;
        if (m_board->getFigureAtPos(numPos,LetterPosition::LET_POS_C) != nullptr) return false;
        if (m_board->getFigureAtPos(numPos,LetterPosition::LET_POS_D) != nullptr) return false;
        letPositions.push_back(LetterPosition::LET_POS_B);
        letPositions.push_back(LetterPosition::LET_POS_C);
        letPositions.push_back(LetterPosition::LET_POS_D);
    } else {
        //first we have to check if the fields between rook and king are empty
        if (m_board->getFigureAtPos(numPos,LetterPosition::LET_POS_F) != nullptr) return false;
        if (m_board->getFigureAtPos(numPos,LetterPosition::LET_POS_G) != nullptr) return false;
        letPositions.push_back(LetterPosition::LET_POS_F);
        letPositions.push_back(LetterPosition::LET_POS_G);
    }
    for (const auto & letPos : letPositions) {
        CheckAttacksOnField * checkAttacksOnField = new CheckAttacksOnField(m_board, (FigureColor)m_king->getFigColor(), numPos, letPos);
        if (checkAttacksOnField->check()) { //if there is some attack we cannot make
            delete checkAttacksOnField;
            return false;
        } else {
            delete checkAttacksOnField;
        }
    }
    //save the field to move king when castling
    m_fieldToCastle = make_pair(numPos, m_king->getLetPos() + 2 * m_castlingSide);

    return true;
}

/**
 * main function to check if the castling can be done with the given state of game
 * @return true in case of such possibility; false otherwise
 */
bool Castling::check() {
    if (!checkKing()) return false; //check if there was no move with the king
    if (!checkRooks()) return false; //check if there was no moves with the rooks
    if (checkCheck()) return false; //check if king is not checked
    if (!checkFieldsBetweenKingAndRook()) return false; //check if there are no attacks on fields between king and rook
    return true;
}

