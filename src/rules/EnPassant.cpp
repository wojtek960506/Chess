#include "EnPassant.hpp"

//return true if the en passant on the current side of the figuer can be done
/**
 * function checks if the en passant capture on the figure can be done
 * @return true if the en passant on the current side can be done; in case of no such possibility or figure which is no pawn return false
 */
bool EnPassant::check() {
    if (m_figure->getFigType() != FigureType::PAWN) return false;
    if (m_figure->getFigColor() == FigureColor::WHITE && m_figure->getNumPos() != NumericPosition::NUM_POS_5)
        return false;
    if (m_figure->getFigColor() == FigureColor::BLACK && m_figure->getNumPos() != NumericPosition::NUM_POS_4)
        return false;
    return checkPawn();
}

/**
 * function cheks if the en passant on the pawn on the current side of our pawn can be done
 * @return true in case of such possibility; false otherwise
 */
bool EnPassant::checkPawn() {
    if (m_figure->getLetPos() + m_side > (int)(BOARD_SIZE-1) || m_figure->getLetPos() + m_side < 0)
        return false;
    try {
        Figure *figure = m_board->getFigureAtPos(m_figure->getNumPos(), m_figure->getLetPos() + m_side);
        if (figure == nullptr) return false;
        if (figure->getFigType() != FigureType::PAWN) return false;

        return dynamic_cast<Pawn *>(figure)->canBeCapturedWithEnPassant();
    } catch (const InvalidPosition & e) {
        return false;
    }
}
