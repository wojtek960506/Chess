#include "Figure.hpp"

/**
 * updates all possible movements for bishop based on its king position and board state
 * @param king
 * @param board
 * @param fullRangeOfMoves
 * @param changeNumPos
 * @param changeLetPos
 */
void Bishop::getMove(King * king, Board * board, vector<FieldToMove> & fullRangeOfMoves, const int & changeNumPos, const int & changeLetPos) {
    int tmpNumPos = m_numPos + changeNumPos;
    int tmpLetPos = m_letPos + changeLetPos;
    Figure * figure;
    try {
        while (true) {
            figure = board->getFigureAtPos(tmpNumPos, tmpLetPos);
            if (figure == nullptr) {
                //if this movement can cause check than not add it
                if (checkCastlingAfterMovement(king, board, m_numPos, m_letPos, tmpNumPos, tmpLetPos)) {
                    tmpNumPos += changeNumPos; tmpLetPos += changeLetPos; continue;
                }
                //add field to move
                fullRangeOfMoves.push_back(FieldToMove(tmpNumPos, tmpLetPos, MoveType::NORMAL));
                tmpNumPos += changeNumPos; tmpLetPos += changeLetPos; continue;
            } else {
                if (figure->getFigType() == FigureType::KING) {
                    if (figure->getFigColor() == m_figColor) break;
                    //if this movement can cause check than not add it
                    if (checkCastlingAfterMovement(king, board, m_numPos, m_letPos, tmpNumPos, tmpLetPos)) break;
                    //add field to move
                    fullRangeOfMoves.push_back(FieldToMove(tmpNumPos, tmpLetPos, MoveType::CHECK)); break;
                } else {
                    if (figure->getFigColor() == m_figColor) break;
                    //if this movement can cause check than not add it
                    if (checkCastlingAfterMovement(king, board, m_numPos, m_letPos, tmpNumPos, tmpLetPos)) break;
                    //add field to move
                    fullRangeOfMoves.push_back(FieldToMove(tmpNumPos, tmpLetPos, MoveType::CAPTURE)); break;
                }
            }
        }
    } catch (const InvalidPosition & e) {}
}

/**
 * returns all possible moves for bishop based on current state of board and its king position
 * @param king
 * @param board
 * @return
 */
vector < FieldToMove > Bishop::getFullRangeOfMoves(King * king, Board * board) {
    vector < FieldToMove > fullRangeOfMoves;
    int directions[2] = {-1,1};
    vector<pair<int,int>> allDirections;
    for (int i : directions) for (int j : directions) allDirections.push_back(make_pair(i,j));
    for (const auto & direction : allDirections)
        getMove(king, board, fullRangeOfMoves, direction.first, direction.second);
    return fullRangeOfMoves;
}

