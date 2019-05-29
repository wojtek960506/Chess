#include "Stalemate.hpp"

//we just check if we can do any movement at the time. If not it means that there is a stalemate
/**
 * function to check if stalemate is present for the actual state of game;
 * we check stalemate when the current player's king is not checked;
 * if the player cannot move in such case then game ands with the draw
 * @return true if player cannot move with any of its figures; false otherwise
 */
bool Stalemate::check() {
    for (const auto & figure : *m_game->getFiguresPtr()) {
        vector < FieldToMove > tmpFieldsToMove;

        FigureColor opponentPlayer;
        if (m_game->getCurrentPlayer() == FigureColor::WHITE) {
            opponentPlayer = FigureColor::BLACK;
        } else {
            opponentPlayer = FigureColor::WHITE;
        }


        //we check only figures of current player
        if (figure->getFigColor() != opponentPlayer) {
            continue;
        }

        if (opponentPlayer == FigureColor::WHITE) {
            tmpFieldsToMove = figure->getFullRangeOfMoves(m_game->getWhiteKing(), m_board);
        } else {//current player is black
            tmpFieldsToMove = figure->getFullRangeOfMoves(m_game->getBlackKing(), m_board);
        }
        //some figure can move
        if (tmpFieldsToMove.size() > 0) return false;
    }
    //there was no figure with which we can move so there is draw (no check on king and no possibility to move is stalemate)
    return true;
}