#ifndef PROMOTION_HPP
#define PROMOTION_HPP

#include "Rule.hpp"
#include "../main_logic/Game.hpp"

class Game;

/**
 * class to represent the rule of promotion of the pawn - pawn turns into more powerful figure (except king)
 */
class Promotion : public Rule {
public:
    Promotion (Board * board, Figure * figure) : Rule(board), m_figure(figure) {}
    bool check() override;
    void promotePawn(Game * game, FigureType figureType);
private:
    Figure * m_figure;
};


#endif //PROMOTION_HPP
