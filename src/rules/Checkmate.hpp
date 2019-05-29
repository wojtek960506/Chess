#include <utility>

#ifndef CHECKMATE_HPP
#define CHECKMATE_HPP

#include "Rule.hpp"

/**
 * class to represent the rule of checkmate; this class has to be always created after checking the check
 */
class Checkmate : public Rule {
public:
    Checkmate(Board * board, King * king, vector<Figure*>  attackFigures)
        : Rule(board), m_king(king), m_attackFigures(std::move(attackFigures)) {}
    bool check() override;


private:
    King * m_king;
    vector<Figure*> m_attackFigures; //store figures which check the king
    vector<pair<int,int>> m_fieldsToBlock;

    void getFieldsToBlock();
    bool findSaviourForKing();
};

pair<int,int> getRelativeDirection(const int & kingNumPos, const int & kingLetPos,
                                   const int & figNumPos, const int & figLetPos);

#endif //CHECKMATE_HPP
