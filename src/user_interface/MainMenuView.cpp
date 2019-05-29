#include "MainMenuView.hpp"

#include <iostream>
using namespace std;


void MainMenuView::drawButton(const char * text, const char * font, int middle_x, int middle_y) {
    SDL_Rect rect = drawText(   m_renderer, middle_x, middle_y, text, font, MAIN_MENU_BUTTON_FONT_SIZE,
                          MAIN_MENU_BUTTON_FONT_R, MAIN_MENU_BUTTON_FONT_G, MAIN_MENU_BUTTON_FONT_B,
                          MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);
    m_buttons.push_back(SDL_Button(rect.x, rect.y, rect.w, rect.h));
}

void MainMenuView::drawButtons() {

    //for CLion
    //const char * font = "../src/fonts/OpenSans-Bold.ttf";

    //for makefile
    //const char * font = "./src/fonts/OpenSans-Bold.ttf";

    //const char * font = CHESS_FONT_FILE;

    drawButton("NEW GAME", m_font_name, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 1.25 * MAIN_MENU_BUTTON_FONT_SIZE);
    drawButton("LOAD GAME", m_font_name, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 0.5 * MAIN_MENU_BUTTON_FONT_SIZE);
    drawButton("HELP", m_font_name, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 2.25 * MAIN_MENU_BUTTON_FONT_SIZE);
    drawButton("EXIT", m_font_name, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 4 * MAIN_MENU_BUTTON_FONT_SIZE);
}

void MainMenuView::drawTitle() {

    drawText(   m_renderer, SCREEN_WIDTH/2, MAIN_MENU_TITLE_FONT_SIZE*3/5, "CHESS", m_font_name, MAIN_MENU_TITLE_FONT_SIZE,
                MAIN_MENU_TITLE_FONT_R, MAIN_MENU_TITLE_FONT_G, MAIN_MENU_TITLE_FONT_B,
                MAIN_MENU_BACKGROUND_R, MAIN_MENU_BACKGROUND_G, MAIN_MENU_BACKGROUND_B);

    drawAuthor();
    /*
    drawText(   m_renderer, SCREEN_WIDTH-135, SCREEN_HEIGHT-MAIN_MENU_AUTHOR_FONT_SIZE, "Author: Wojciech Zielinski",
                m_font_name, MAIN_MENU_AUTHOR_FONT_SIZE,
                MAIN_MENU_AUTHOR_FONT_R, MAIN_MENU_AUTHOR_FONT_G, MAIN_MENU_AUTHOR_FONT_B,
                MAIN_MENU_BACKGROUND_R, MAIN_MENU_BACKGROUND_G, MAIN_MENU_BACKGROUND_B);
    */
     }

WhichViewNext MainMenuView::run() {
	bool quit = false; //main loop flag
	SDL_Event e; //event handler

    SDL_SetRenderDrawColor( m_renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( m_renderer );

    drawTitle();
    drawButtons();

    WhichViewNext returnValue = WhichViewNext::DEFAULT_VALUE;

    SDL_RenderPresent( m_renderer );
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if( e.type == SDL_QUIT ) {
			    quit = true;
			    returnValue = WhichViewNext::EXIT;
			}

			//check if any button was clicked
            for (unsigned int i = 0 ; i < m_buttons.size() ; ++i) {
                if (m_buttons[i].handleEvent(&e)) {
                    quit = true;
                    switch (i) {
                        case 0:
                            returnValue = WhichViewNext::CHOOSE_PLAYER;
                            break;
                        case 1:
                            returnValue = WhichViewNext::LOAD_GAME;
                            break;
                        case 2:
                            returnValue = WhichViewNext::HELP;
                            break;
                        default: //in case of 3 or any number (which is a mistake close the app)
                            returnValue = WhichViewNext::EXIT;
                            break;

                    }

                    //returnValue = (WhichViewNext)i;
                }
            }
		}
	}
	return returnValue;
}
