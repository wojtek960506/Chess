#include "Figure.hpp"
#include "../rules/EnPassant.hpp"
#include "../rules/Check.hpp"

/**
 * overloaded function of move for pawn.
 * We have to update ability to do en passant on this pawn.
 * @param board
 * @param numPos
 * @param letPos
 */
void Pawn::move(Board * board, const int & numPos, const int & letPos) {
    if (numPos < 0 || numPos > (int)(BOARD_SIZE-1) || letPos < 0 || letPos >  (int)(BOARD_SIZE-1)) throw InvalidPosition();
    //check if the en passant can be done on this pawn (only when it is the first move of 2 fields)
    if (m_moves == 0 && abs(m_numPos - numPos) == 2) m_enPassantFlag = true;
    //update position
    ++m_moves;
    m_numPos = numPos;
    m_letPos = letPos;
    board->putFigure(this, numPos, letPos);
    //cout << "Pawn move" << endl;
}

/**
 * it checks if the castling is possible after execution of en passant capture
 * @param king
 * @param board
 * @param numPosBefore
 * @param letPosBefore
 * @param numPosAfter
 * @param letPosAfter
 * @return
 */
bool Pawn::checkCastlingAfterMovementEnPassant (King * king, Board * board,
                                                const int & numPosBefore, const int & letPosBefore,
                                                const int & numPosAfter, const int & letPosAfter) {

    //we have to store temporarily pawn which is capturing and the pawn which is captured
    Figure * tmpFigureBefore = board->getFigureAtPos(numPosBefore, letPosBefore);
    Figure * tmpFigureEnPassant = board->getFigureAtPos(numPosBefore, letPosAfter);

    //reset those fields
    board->putFigure(nullptr, numPosBefore, letPosBefore);
    board->putFigure(nullptr, numPosBefore, letPosAfter);

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
    board->putFigure(tmpFigureEnPassant, numPosBefore, letPosAfter);

    return result;

}

/**
 * * updates all possible movements for pawn of its possibility to make en passant movement.
 * It is based on its king position, its color and board state.
 * @param king
 * @param board
 * @param fullRangeOfMoves
 * @param numPos
 * @param letPos
 * @param moves
 * @param color
 */
void Pawn::getNormalMove(King * king, Board * board, vector<FieldToMove> & fullRangeOfMoves, const int & numPos, const int & letPos,
        const unsigned int & moves, FigureColor color) {
    int colorMove = 0;
    if (color == FigureColor::WHITE) colorMove = -1;
    else colorMove = 1;

    if (board->getFigureAtPos(numPos+colorMove, letPos) != nullptr) return; //cannot move if there is something in front

    //if this movement can cause check than not add it
    if (!checkCastlingAfterMovement(king, board, m_numPos, m_letPos, numPos + colorMove, letPos)) {
        //add field to move (one step forward)
        fullRangeOfMoves.push_back(FieldToMove(numPos + colorMove, letPos, MoveType::NORMAL));
    }
    //two steps forward
    if ( moves == 0) {
        if (board->getFigureAtPos(numPos+2*colorMove, letPos) != nullptr) return; //cannot move if there is something in front
        //if this movement can cause check than not add it
        if (!checkCastlingAfterMovement(king, board, m_numPos, m_letPos, numPos + 2 * colorMove, letPos)) {
            //add field to move
            fullRangeOfMoves.push_back(FieldToMove(numPos + 2 * colorMove, letPos, MoveType::NORMAL));
        }
    }
}

/**
 * updates all possible movements for pawn of its possibility to make a standard capture.
 * It is based on its king position and board state.
 * @param king
 * @param board
 * @param fullRangeOfMoves
 * @param numPos
 * @param letPos
 */
void Pawn::getCaptureMove(King * king, Board * board, vector<FieldToMove> & fullRangeOfMoves, const int & numPos,
        const int & letPos) {
    try {
        Figure * figure = board->getFigureAtPos(numPos, letPos);
        if (figure != nullptr && figure->getFigColor() != m_figColor) {
            if (figure->getFigType() == FigureType::KING) {
                //if this movement can cause check than not add it
                if (checkCastlingAfterMovement(king, board, m_numPos, m_letPos, numPos, letPos)) return;
                //add field to move
                fullRangeOfMoves.push_back(FieldToMove(numPos, letPos, MoveType::CHECK));
            } else {
                //if this movement can cause check than not add it
                if (checkCastlingAfterMovement(king, board, m_numPos, m_letPos, numPos, letPos)) return;
                //add field to move
                fullRangeOfMoves.push_back(FieldToMove(numPos, letPos, MoveType::CAPTURE));
            }
        }
    } catch (const InvalidPosition & e) {}
}

/**
 * updates all possible movements for pawn of its possibility to make en passant movement.
 * It is based on its king position and board state.
 * @param king
 * @param board
 * @param fullRangeOfMoves
 * @param changeNumPos
 * @param changeLetPos
 */
void Pawn::getEnPassantMove(King * king, Board * board, vector<FieldToMove> & fullRangeOfMoves, const int & numPos,
        const int & letPos, EnPassantSide side) {
    EnPassant * enPassant = new EnPassant(board, this, side);
    if (enPassant->check()) {
        int colorMove = 0;
        if (m_figColor == FigureColor::WHITE) colorMove = -1;
        else colorMove = 1;
        //if this movement can cause check than not add it

        if (checkCastlingAfterMovementEnPassant(king, board, m_numPos, m_letPos, numPos + colorMove, letPos + side)) return;
        //add field to move
        fullRangeOfMoves.push_back(FieldToMove(numPos + colorMove, letPos + side, MoveType::EN_PASSANT));
    }
    delete enPassant;
}

/**
 * returns all possible moves for knight based on current state of board and its king position
 * @param king
 * @param board
 * @return
 */
vector < FieldToMove > Pawn::getFullRangeOfMoves(King * king, Board * board) {

    vector < FieldToMove > fullRangeOfMoves;
    int colorMove = 0;
    if (m_figColor == FigureColor::WHITE) colorMove = -1;
    else colorMove = 1; //color is balck
    //check move
    getNormalMove(king, board, fullRangeOfMoves, m_numPos, m_letPos, m_moves, m_figColor);
    //check normal capture
    getCaptureMove(king, board, fullRangeOfMoves, m_numPos+colorMove, m_letPos-1);
    getCaptureMove(king, board, fullRangeOfMoves, m_numPos+colorMove, m_letPos+1);
    //check en passant capture
    getEnPassantMove(king, board, fullRangeOfMoves, m_numPos, m_letPos, EnPassantSide::EN_LEFT);
    getEnPassantMove(king, board, fullRangeOfMoves, m_numPos, m_letPos, EnPassantSide::EN_RIGHT);
    return fullRangeOfMoves;
}

