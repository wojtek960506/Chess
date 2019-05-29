#ifndef DRAWBOARDRECT_HPP
#define DRAWBOARDRECT_HPP

extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}

#include "../main_logic/ConstantsAndEnums.hpp"
#include "Draw.hpp"

/**
 * class used to represent and draw the board's field
 */
class DrawBoardRect {
public:
    DrawBoardRect(SDL_Renderer* renderer, BoardRectColor rectColor) : m_renderer(renderer), m_rectColor(rectColor) {}
    DrawBoardRect(SDL_Renderer * renderer, BoardRectColor rectColor, int beginX, int beginY, FigureColor figColor,
            FigureType figType, RectSurrColor surr, bool marked, int width = BOARD_FIELD_SIZE, int height = BOARD_FIELD_SIZE) :
            m_renderer(renderer), m_rectColor(rectColor), m_beginX(beginX), m_beginY(beginY), m_figColor(figColor),
            m_figType(figType), m_surr(surr), m_marked(marked), m_width(width), m_height(height) {}
    ~DrawBoardRect() { m_renderer = nullptr; }
    void setRectColor (const BoardRectColor & rectColor) { m_rectColor = rectColor; }
    void setBeginPos (const int & beginX, const int & beginY) { m_beginX = beginX; m_beginY = beginY; }
    void setFigure(const FigureType & figType, const FigureColor & figColor) {m_figType = figType; m_figColor = figColor; }
    void setFigColor (const FigureColor & figColor) { m_figColor = figColor; }
    void setFigType (const FigureType & figType) { m_figType = figType; }
    void setSurr (const RectSurrColor & surr) { m_surr = surr; }
    void setMarked (bool marked) { m_marked = marked; }
    void setChecked (bool checked) { m_checked = checked; }
    void draw();

    std::string m_extension = CHESS_IMAGE_DIRECTORY; //"../src/chess_figures/";
private:
    SDL_Renderer * m_renderer = nullptr;
    BoardRectColor m_rectColor;
    int m_beginX = 0;
    int m_beginY = 0;
    FigureColor m_figColor = FigureColor::NONE_C;
    FigureType m_figType = FigureType::NONE_T;
    RectSurrColor m_surr = RectSurrColor::NONE_S;
    bool m_marked = false; //when there is move from this rect
    bool m_checked = false; //when this field is included in check
    int m_width;  //= BOARD_FIELD_SIZE;
    int m_height; //= BOARD_FIELD_SIZE;

    void drawFigure();
};

#endif //DRAWBOARDRECT_HPP
