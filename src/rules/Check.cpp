#include "Check.hpp"
#include "CheckAttacksOnField.hpp"

//returns true if the king is checked
/**
 * main function to check if the king with the given color is checked
 * @return true in case of checked king; false otherwise
 */
bool Check::check() {
    CheckAttacksOnField * checkAttacksOnField = new CheckAttacksOnField(m_board, (FigureColor)m_king->getFigColor(), m_king->getNumPos(), m_king->getLetPos());
    bool checkResult = checkAttacksOnField->check();
    m_attackFigures = checkAttacksOnField->getAttackFigures();
    delete checkAttacksOnField;

    return checkResult;
}