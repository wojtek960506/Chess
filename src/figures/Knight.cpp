#include "Figure.hpp"

/**
 * updates all possible movements for knight based on its king position and board state
 * @param king
 * @param board
 * @param fullRangeOfMoves
 * @param changeNumPos
 * @param changeLetPos
 */
void Knight::getMove(King * king, Board * board, vector<FieldToMove> & fullRangeOfMoves, const int & numPos, const int & letPos ) {
    try{
        Figure * figure = board->getFigureAtPos(numPos, letPos);
        MoveType moveType = MoveType::NORMAL;
        if (figure != nullptr) {
            if (figure->getFigColor() == m_figColor) return; //cannot capture figure with the same color
            if (figure->getFigType() == FigureType::KING) moveType = MoveType::CHECK;
            else moveType = MoveType::CAPTURE;
        }
        //if this movement can cause check than not add it
        if (checkCastlingAfterMovement(king, board, m_numPos, m_letPos, numPos, letPos)) return;
        //add field to move
        fullRangeOfMoves.push_back(FieldToMove(numPos, letPos, moveType));
    } catch (const InvalidPosition & e) {}
}

/**
 * returns all possible moves for knight based on current state of board and its king position
 * @param king
 * @param board
 * @return
 */
vector < FieldToMove > Knight::getFullRangeOfMoves(King * king, Board * board) {
    vector < FieldToMove > fullRangeOfMoves;

    const int tmpForMoves1[2] = {-2,2};
    const int tmpForMoves2[2] = {-1,1};
    vector <pair<int,int>> allMovesCombinations;
    for (int i : tmpForMoves1) {
        for (int j : tmpForMoves2) {
            allMovesCombinations.push_back(make_pair(i, j));
            allMovesCombinations.push_back(make_pair(j, i));
        }
    }
    for (const auto & move : allMovesCombinations)
        getMove(king, board, fullRangeOfMoves, m_numPos + move.first, m_letPos + move.second);

    return fullRangeOfMoves;
}