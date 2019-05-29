#ifndef ENPASSANT_HPP
#define ENPASSANT_HPP

#include "Rule.hpp"

/**
 * class to represent the rule of en passant
 */
class EnPassant : public Rule {
public:
    EnPassant (Board * board, Figure * figure, EnPassantSide side) : Rule(board), m_figure(figure), m_side(side) {};
    virtual bool check();
private:
    Figure * m_figure;
    EnPassantSide m_side;
    bool checkPawn();

};

#endif //ENPASSANT_HPP
