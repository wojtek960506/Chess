#ifndef PROMOTIONVIEW_HPP
#define PROMOTIONVIEW_HPP

extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}

#include <vector>
#include "../main_logic/ConstantsAndEnums.hpp"
#include "BoardFieldButton.hpp"
#include "Draw.hpp"
#include "DrawBoardRect.hpp"

using namespace std;

/**
 * class to represent the screen of choosing figure to which the pawn will be promoted;
 * it don't inherit from BaseView, bcause it is used inside the NewGameView
 */
class PromotionView {
public:
    PromotionView(SDL_Renderer* renderer, FigureColor figureColor);
    FigureType run();
private:
    SDL_Renderer* m_renderer = nullptr;
    FigureColor m_figureColor;
    vector <BoardFieldButton> m_buttons;

    const char * m_font_name = CHESS_FONT_FILE; //"../src/fonts/OpenSans-Bold.ttf";

    void clearBackground();
    void drawTitle();
    void drawFiguresToChoose();
    void setButtons();

};

#endif //PROMOTIONVIEW_HPP
