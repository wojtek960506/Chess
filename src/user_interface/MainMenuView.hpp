#ifndef MAINMENU_HPP
#define MAINMENU_HPP

extern "C" {
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
}

#include <iostream>
#include <vector>

#include "BaseView.hpp"


using namespace std;

/**
 * class to represent screen of the main menu
 */
class MainMenuView : public BaseView {
public:
	MainMenuView(SDL_Renderer * renderer) : BaseView(renderer) {}
	WhichViewNext run() override;
private:
    void drawButtons();
    void drawButton(const char * text, const char * font, int middle_x, int middle_y);
    void drawTitle();

	vector <SDL_Button> m_buttons;
};

#endif //MAINMENU_HPP