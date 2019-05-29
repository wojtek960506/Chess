#ifndef RULE_HPP
#define RULE_HPP

#include "../main_logic/Board.hpp"
#include "../figures/Figure.hpp"
#include <vector>

/**
 * abstract class which represents the interface to follow by the rules in the chess game
 */
class Rule {
public:
    Rule(Board * board) : m_board(board) {}
    virtual ~Rule() { m_board = nullptr; }
    virtual bool check() = 0;
protected:
    Board * m_board;
};


#endif //RULE_HPP
