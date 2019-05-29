#ifndef CHECK_HPP
#define CHECK_HPP

#include "Rule.hpp"
#include "CheckAttacksOnField.hpp"

#include <utility>

/**
 * class to represent the rule of check
 */
class Check : public Rule {
public:
    Check (Board * board, King * king)
        : Rule(board), m_king(king) {}
    bool check() override;
    const vector<Figure*> getAttackFigures() const { return m_attackFigures; }
private:
    King * m_king;
    vector<Figure*> m_attackFigures; //store figures which check the king
};

#endif //CHECK_HPP
