#include <utility>


#ifndef CASTLING_HPP
#define CASTLING_HPP

#include "Rule.hpp"
#include "../main_logic/ConstantsAndEnums.hpp"

/**
 * class to represent the rule of castling
 */
class Castling : public Rule {
public:
    Castling(Board * board, King * king, CastlingSide castlingSide)
        : Rule(board),  m_king(king), m_castlingSide(castlingSide){}
    bool check() override;
    const pair<int,int> & getFieldToCastle() const { return m_fieldToCastle; }
private:
    King * m_king;
    CastlingSide m_castlingSide;
    pair<int,int> m_fieldToCastle;
    bool checkKing() const;
    bool checkRook(const int & numPos, const int & letPos) const;
    bool checkRooks() const;
    bool checkCheck() const;
    bool checkFieldsBetweenKingAndRook();
};

#endif //CASTLING_HPP
