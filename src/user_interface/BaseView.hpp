#ifndef BASEVIEW_HPP
#define BASEVIEW_HPP

extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_types.h>
}

#include <iostream>

#include "SDL_Button.hpp"
#include "../main_logic/ConstantsAndEnums.hpp"
#include "Draw.hpp"


using namespace std;

/**
 * abstract class which is an inteface to all views in application
 */
class BaseView {
public:
    BaseView(SDL_Renderer* renderer) : m_renderer(renderer) {}
    virtual ~BaseView() { m_renderer = nullptr; }
    virtual WhichViewNext run() = 0;

    const char * m_font_name = CHESS_FONT_FILE;

    void drawAuthor( const Uint8 authorFont_R = MAIN_MENU_AUTHOR_FONT_R,
                     const Uint8 authorFont_G = MAIN_MENU_AUTHOR_FONT_G,
                     const Uint8 authorFont_B = MAIN_MENU_AUTHOR_FONT_B,
                     const Uint8 authorBackground_R = MAIN_MENU_BACKGROUND_R,
                     const Uint8 authorBackground_G = MAIN_MENU_BACKGROUND_G,
                     const Uint8 authorBackground_B = MAIN_MENU_BACKGROUND_B) {

        drawText(   m_renderer, SCREEN_WIDTH-135, SCREEN_HEIGHT-MAIN_MENU_AUTHOR_FONT_SIZE, "Author: Wojciech Zielinski",
                    m_font_name, MAIN_MENU_AUTHOR_FONT_SIZE,
                    authorFont_R, authorFont_G, authorFont_B, authorBackground_R, authorBackground_G, authorBackground_B);
    }

protected:
    SDL_Renderer* m_renderer = nullptr;
};

#endif //BASEVIEW_HPP
