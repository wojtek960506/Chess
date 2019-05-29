#ifndef ENDGAMEVIEW_HPP
#define ENDGAMEVIEW_HPP

#include "BaseView.hpp"
#include <vector>

/**
 * class to represent the screen with the result of the game
 */
class EndGameView : public BaseView {
public:
    EndGameView(SDL_Renderer * renderer, GameResult gameResult) : BaseView(renderer), m_gameResult(gameResult) {}
    WhichViewNext run() override;

private:
    GameResult m_gameResult;
    std::vector <SDL_Button> m_buttons;

    void setButtons();
    void drawResult();
    void drawBackground();
};

#endif //ENDGAMEVIEW_HPP
