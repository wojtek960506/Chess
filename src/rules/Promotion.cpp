#include "Promotion.hpp"

/**
 * function to turn pawn into some more powerful figure
 * @param game - current state of the game to with we apply changes
 * @param figureType - type of figure into which the pawn is changed
 */
void Promotion::promotePawn(Game * game, FigureType figureType) {
    //store position and color of pawn before its removal
    int tmpNumPos = m_figure->getNumPos();
    int tmpLetPos = m_figure->getLetPos();
    FigureColor tmpFigColor = (FigureColor)m_figure->getFigColor();

    //find a pawn
    auto figIt = game->getFiguresPtr()->find(m_figure);
    //erase figure from set of figures
    game->getFiguresPtr()->erase(figIt);
    //delete figure from memory and reset its position on board
    delete m_figure;
    m_figure = nullptr;
    m_board->resetPtrAtPos(tmpNumPos,tmpLetPos);

    //add new figure to game
    switch (figureType) {
        case FigureType::QUEEN:
            game->addFigure(new Queen(tmpFigColor, tmpNumPos, tmpLetPos));
            break;
        case FigureType::ROOK:
            game->addFigure(new Rook(tmpFigColor, tmpNumPos, tmpLetPos));
            break;
        case FigureType::BISHOP:
            game->addFigure(new Bishop(tmpFigColor, tmpNumPos, tmpLetPos));
            break;
        case FigureType::KNIGHT:
            game->addFigure(new Knight(tmpFigColor, tmpNumPos, tmpLetPos));
            break;
        default:
            break;
    }

}

/**
 * function to check if the promotion of pawn can be done - pawn get to the last (for its point of view) side of board
 * @return true in case of such possibility; false otherwise
 */
bool Promotion::check() {
    //only pawn can be promoted
    if (m_figure->getFigType() != FigureType::PAWN) return false;
    //white pawn is promoted when it reaches rank number 8
    if (m_figure->getFigColor() == FigureColor::WHITE) {
        return m_figure->getNumPos() == NumericPosition::NUM_POS_8;
    } else { //black pawn is promoted when it reaches rank number 1
        return m_figure->getNumPos() == NumericPosition::NUM_POS_1;
    }
}