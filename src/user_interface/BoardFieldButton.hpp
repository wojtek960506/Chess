#ifndef BOARDFIELDBUTTON_HPP
#define BOARDFIELDBUTTON_HPP

#include "SDL_Button.hpp"
#include "../main_logic/ConstantsAndEnums.hpp"

/**
 * class to represent button on the field (used to evaluate movements of normal player)
 */
class BoardFieldButton : public SDL_Button {
public:
    BoardFieldButton(   const unsigned int & x, const unsigned int & y, const unsigned int & width,
            const unsigned int & height, const int & numPos, const int & letPos)
                : SDL_Button(x,y,width,height), m_numPos(numPos), m_letPos(letPos) {
        if (m_numPos < 0 || m_numPos > (int)(BOARD_SIZE-1) || m_letPos < 0 || m_letPos > (int)(BOARD_SIZE-1))
            throw InvalidPosition();
    }
    int getNumPos() const { return m_numPos; }
    int getLetPos() const { return m_letPos; }
private:
    int m_numPos;
    int m_letPos;
                };

#endif //BOARDFIELDBUTTON_HPP
