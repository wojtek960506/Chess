#ifndef FIELDTOMOVE_HPP
#define FIELDTOMOVE_HPP

#include "ConstantsAndEnums.hpp"

/**
 * class to represent what type of move can be done on the given position
 */
class FieldToMove {
public:
    FieldToMove(const int & numPos, const int & letPos, MoveType moveType)
        : m_numPos(numPos), m_letPos(letPos), m_moveType(moveType) {}
    int getNumPos() const { return m_numPos; }
    int getLetPos() const { return m_letPos; }
    MoveType getMoveType() const { return m_moveType; }
private:
    int m_numPos;
    int m_letPos;
    MoveType m_moveType;
};

#endif //FIELDTOMOVE_HPP
