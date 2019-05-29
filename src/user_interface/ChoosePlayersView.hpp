#ifndef CHOOSEPLAYERSVIEW_HPP
#define CHOOSEPLAYERSVIEW_HPP

#include "BaseView.hpp"
#include "../main_logic/ConstantsAndEnums.hpp"
#include <vector>

/**
 * view to choose types of players before starting the game with the standard beginning
 */
class ChoosePlayersView : public BaseView {
public:
    ChoosePlayersView(SDL_Renderer * renderer) : BaseView(renderer) {}
    WhichViewNext run() override;

    PlayerType m_playerWhite = PlayerType::NORMAL_PLAYER;
    PlayerType m_playerBlack = PlayerType::NORMAL_PLAYER;
private:
    void setButtons();
    void drawTitle();
    void drawImages();
    void redrawPlayerWhite();
    void redrawPlayerBlack();
    void changePlayerWhite();
    void changePlayerBlack();

    std::vector <SDL_Button> m_buttons;
};

#endif //CHOOSEPLAYERSVIEW_HPP
