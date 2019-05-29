#ifndef LOADGAMEVIEW_HPP
#define LOADGAMEVIEW_HPP

#include "BaseView.hpp"
#include "../main_logic/ReadState.hpp"

#include <vector>

/**
 * class to represent the screen of loading the game from file
 */
class LoadGameView : public BaseView {
public:
    LoadGameView(SDL_Renderer * renderer, Game *& game) : BaseView (renderer), m_game(game) {}
    WhichViewNext run() override;
private:
    Game *& m_game;
    vector <SDL_Button> m_buttons;
    string m_filename = "state";

    void drawButtons();
    void drawButton(const char * text, const char * font, int middle_x, int middle_y);
    void drawTitle();
};

#endif //LOADGAMEVIEW_HPP
