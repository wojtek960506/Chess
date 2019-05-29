#include "Figure.hpp"
#include "../rules/Castling.hpp"
#include "../rules/CheckAttacksOnField.hpp"

/**
 * updates all possible movements for king based on board state
 * @param king - unused variable which is necessary for correct overloading of the purely virtual function
 * @param board
 * @param fullRangeOfMoves
 * @param changeNumPos
 * @param changeLetPos
 */
void King::getMove(King * king, Board * board, vector<FieldToMove> & fullRangeOfMoves, const int & numPos, const int & letPos) {
    int tmpNumPos = m_numPos + numPos;
    int tmpLetPos = m_letPos + letPos;
    try{
        //check if the king will not be attacked when he will move on this field
        CheckAttacksOnField * checkAttacksOnField = new CheckAttacksOnField(board, m_figColor, tmpNumPos, tmpLetPos);
        if (checkAttacksOnField->check()) { //if there is some attack we cannot move a king there
            delete checkAttacksOnField;
            return;
        } else {
            delete checkAttacksOnField;
        }
        //if (checkAttacksOnField(board, nullptr, tmpNumPos, tmpLetPos)) return; //if there is some attack we cannot move a king there
        Figure * figure = board->getFigureAtPos(tmpNumPos, tmpLetPos);
        if (figure == nullptr) {

            //if (!checkCastlingAfterMovement(king, board, m_numPos, m_letPos, tmpNumPos, tmpLetPos)) {
                fullRangeOfMoves.push_back(FieldToMove(tmpNumPos, tmpLetPos, MoveType::NORMAL));
                return;
            //}
        } else {
            if (figure->getFigColor() == m_figColor) return; //cannot move on the field where there is our figure
            else {
                //if (!checkCastlingAfterMovement(king, board, m_numPos, m_letPos, tmpNumPos, tmpLetPos)) {
                    fullRangeOfMoves.push_back(FieldToMove(tmpNumPos, tmpLetPos, MoveType::CAPTURE));
                    return;
                //}
            }
        }
    } catch (const InvalidPosition & e) {}
}

/**
 * updates full range of moves for king of the possibility of castling
 * @param board
 * @param fullRangeOfMoves
 */
void King::checkCastling(Board * board, vector<FieldToMove> & fullRangeOfMoves) {
    Castling * castlingLeft = new Castling(board, this, CastlingSide::CASTLING_LEFT);
    if (castlingLeft->check()) {
        pair<int,int> fieldToCastle = castlingLeft->getFieldToCastle();
        fullRangeOfMoves.push_back(FieldToMove(fieldToCastle.first, fieldToCastle.second, MoveType::CASTLE));
    }
    delete castlingLeft;
    Castling * castlingRight = new Castling(board, this, CastlingSide::CASTLING_RIGHT);
    if (castlingRight->check()) {
        pair<int,int> fieldToCastle = castlingRight->getFieldToCastle();
        fullRangeOfMoves.push_back(FieldToMove(fieldToCastle.first, fieldToCastle.second, MoveType::CASTLE));
    }
    delete castlingRight;
}

/**
 * returns all possible moves for king based on current state of board
 * @param king
 * @param board
 * @return
 */
vector < FieldToMove > King::getFullRangeOfMoves(King * king, Board * board) {
    vector < FieldToMove > fullRangeOfMoves;

    vector<pair<int,int>> allKingMoves = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
    for (const auto & move : allKingMoves) {
        getMove(king, board, fullRangeOfMoves, move.first, move.second);
    }
    checkCastling(board, fullRangeOfMoves);
    return fullRangeOfMoves;
}