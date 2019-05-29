#ifndef HELPVIEW_HPP
#define HELPVIEW_HPP

#include "BaseView.hpp"

#include <vector>

/**
 * class to represent the screen with help informations
 */
class HelpView : public BaseView {
public:
    HelpView(SDL_Renderer * renderer) : BaseView(renderer) {}
    WhichViewNext run() override;
private:
    void drawButtons();
    void drawButton(const char * text, const char * font, int middle_x, int middle_y);
    void drawTitle();

    std::vector <SDL_Button> m_buttons;
};

#endif //HELPVIEW_HPP
