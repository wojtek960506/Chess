#ifndef MOVE_HPP
#define MOVE_HPP

#include "Rule.hpp"
#include "../main_logic/Game.hpp"

/**
 * class to represent the rule of the movement
 * coordinates of the field to move are provided as members of the class
 */
class Move : public Rule {
public:
    Move(Board * board, Game * game, Figure * figure, set<Figure*> * figuresPtr,
            const vector<FieldToMove> & fieldsToMove, const int & numPos, const int & letPos)
                : Rule(board), m_game(game), m_figure(figure), m_figuresPtr(figuresPtr),
                  m_fieldsToMove(fieldsToMove), m_numPos(numPos), m_letPos(letPos) {}
    bool check() override;
    MoveType getMoveType() const { return m_moveType; }
private:
    Game * m_game; //to update set of figures in case of capture
    Figure * m_figure;
    set<Figure*> * m_figuresPtr;
    const vector<FieldToMove> & m_fieldsToMove;
    int m_numPos; //numerical position to move
    int m_letPos; //letter position to move
    MoveType m_moveType = MoveType::NONE;

    bool checkPossibilityToMove();
    void doNormalMove();
    void doCapture();
    void doCastling();
    void doEnPassant();
    void deleteFigure(const int & numPos, const int & letPos);
};

#endif //MOVE_HPP