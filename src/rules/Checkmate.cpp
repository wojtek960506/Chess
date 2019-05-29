#include "Checkmate.hpp"
#include "CheckAttacksOnField.hpp"

//it returns <0,0> if the figure is neither on diagonal nor rank nor file in regard of main figure position
/**
 * function to return the relative direction between the king and the figure
 * @param kingNumPos - numeric position of the king
 * @param kingLetPos - letter position of hte king
 * @param figNumPos - numeric position of the figure
 * @param figLetPos - letter position of the figure
 * @return <0,0> if the figure is neither on diagonal nor file in regard of the main figure's position; otherwise the relative idrection between those two provided figures
 */
pair<int,int> getRelativeDirection(const int & kingNumPos, const int & kingLetPos,
        const int & figNumPos, const int & figLetPos) {
    int num = figNumPos - kingNumPos;
    int let = figLetPos - kingLetPos;
    if (num == 0) {
        if (let == 0) return make_pair(0,0);
        else return make_pair(0,let/abs(let));
    } else if (let == 0) {
        return make_pair(num/abs(num), 0);
    } else {
        if (abs(let) != abs(num)) return make_pair(0,0);
        else return make_pair(num/abs(num),let/abs(num));
    }
}

/**
 * update the fields on which teh attack in king can be blocked;
 * those can be fields on the neither rank or file or diagonal between the king and the attacking figure (not for kinght)
 * or it can be field on which the attacking figure is standing
 */
void Checkmate::getFieldsToBlock() {
    Figure * figure = m_attackFigures[0];
    if (figure->getFigType() == FigureType::KNIGHT)
        m_fieldsToBlock.push_back(make_pair(figure->getNumPos(), figure->getLetPos()));
    else {
        //position of figure relative to position of king
        pair<int,int> relPos = getRelativeDirection(m_king->getNumPos(), m_king->getLetPos(),
                figure->getNumPos(), figure->getLetPos());
        int relPosNum = relPos.first;
        int relPosLet = relPos.second;
        if (relPosNum == 0 && relPosLet == 0) return;

        //at this point we are sure that figure and king are either on the same diagonal or rank or file
        int figNum = figure->getNumPos();
        int figLet = figure->getLetPos();
        int tmpNum = m_king->getNumPos() + relPosNum;
        int tmpLet = m_king->getLetPos() + relPosLet;
        while (tmpNum != figNum && tmpLet != figLet) {
            m_fieldsToBlock.push_back(make_pair(tmpNum, tmpLet));
            tmpNum += relPosNum;
            tmpLet += relPosLet;
        }
        m_fieldsToBlock.push_back(make_pair(figNum, figLet));
    }
}

/**
 * function to check if there is a figure (of king's color) which can capture or block the attacking figure
 * @return true in case of such figure; otherwise false
 */
bool Checkmate::findSaviourForKing() {
    for (const auto & fieldToBlock : m_fieldsToBlock) {

        //we check if the figure which attacks the king can be captured
        FigureColor colorOfAttacker;
        if (m_king->getFigColor() == FigureColor::WHITE) colorOfAttacker = FigureColor::BLACK;
        else colorOfAttacker = FigureColor::WHITE;

        //we checked before that the king cannot capture the offensive figure, so we it cannot now save itself - (the last argument)
        CheckAttacksOnField checkAttacksOnField  (m_board, colorOfAttacker, fieldToBlock.first, fieldToBlock.second, true);
        if (checkAttacksOnField.check()) return true;
    }
    //there is no figure which attacks any of those fields to block the attacking figure
    return false;
}

/**
 * main function to check if there is a checkmate
 * @return true if the king cannot move and there is no figure which can "save" the king; when there are 2 figures attacking
 * the king then it is automatic checkmate, because we cannot block 2 figures with one movement; otherwise return false;
 */
bool Checkmate::check() {
    //check if we can move king anywhere
    if (!m_king->getFullRangeOfMoves(nullptr, m_board).empty()) return false;
    //check if we can block or capture figure which checks the king
    //if there are more then one figure which check the king and we cannot move the king then it is automatically checkmate
    if (m_attackFigures.size() > 1) return true;
    //we assume that we check checkmate when there is check so I will not check if there is zero offensive figures
    getFieldsToBlock();
    return !findSaviourForKing();

}