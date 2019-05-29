#include "EndGameView.hpp"

void EndGameView::setButtons() {
    //main menu button
    SDL_Rect rectMainMenu = drawText(   m_renderer, END_GAME_MAIN_MENU_BUTTON_MIDDLE_X, END_GAME_MAIN_MENU_BUTTON_MIDDLE_Y,
                                "MAIN MENU", m_font_name, MAIN_MENU_BUTTON_FONT_SIZE,
                                MAIN_MENU_BUTTON_FONT_R, MAIN_MENU_BUTTON_FONT_G, MAIN_MENU_BUTTON_FONT_B,
                                MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);
    m_buttons.push_back(SDL_Button(rectMainMenu.x, rectMainMenu.y, rectMainMenu.w, rectMainMenu.h));

    //exit button
    SDL_Rect rectExit = drawText(   m_renderer, END_GAME_EXIT_BUTTON_MIDDLE_X, END_GAME_EXIT_BUTTON_MIDDLE_Y,
                                "EXIT", m_font_name, MAIN_MENU_BUTTON_FONT_SIZE,
                                MAIN_MENU_BUTTON_FONT_R, MAIN_MENU_BUTTON_FONT_G, MAIN_MENU_BUTTON_FONT_B,
                                MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);
    m_buttons.push_back(SDL_Button(rectExit.x, rectExit.y, rectExit.w, rectExit.h));



    /*m_buttons.push_back(SDL_Button( END_GAME_MAIN_MENU_BUTTON_X, END_GAME_MAIN_MENU_BUTTON_Y,
                                    END_GAME_BUTTON_WIDTH, END_GAME_BUTTON_HEIGHT));
    drawFilledRect( m_renderer, END_GAME_BUTTON_WIDTH, END_GAME_BUTTON_HEIGHT,
                    END_GAME_MAIN_MENU_BUTTON_X, END_GAME_MAIN_MENU_BUTTON_Y,
                    MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);
    drawText(   m_renderer, middle_x, middle_y, text, font, MAIN_MENU_BUTTON_FONT_SIZE,
                MAIN_MENU_BUTTON_FONT_R, MAIN_MENU_BUTTON_FONT_G, MAIN_MENU_BUTTON_FONT_B,
                MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);

    //exit button
    m_buttons.push_back(SDL_Button( END_GAME_EXIT_BUTTON_X, END_GAME_EXIT_BUTTON_Y,
                                    END_GAME_BUTTON_WIDTH, END_GAME_BUTTON_HEIGHT));
    drawFilledRect( m_renderer, END_GAME_BUTTON_WIDTH, END_GAME_BUTTON_HEIGHT,
                    END_GAME_EXIT_BUTTON_X, END_GAME_EXIT_BUTTON_Y,
                    MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);*/
}

void EndGameView::drawResult() {
    const char * text;
    Uint8 colorFontR = 0;
    Uint8 colorFontG = 0;
    Uint8 colorFontB = 0;

    Uint8 colorBackR = 0;
    Uint8 colorBackG = 0;
    Uint8 colorBackB = 0;

    switch (m_gameResult) {
        case GameResult::WHITE_WIN:
            text = "WHITE WINS";
            colorFontR = WHITE_COLOR_R;
            colorFontG = WHITE_COLOR_G;
            colorFontB = WHITE_COLOR_B;
            colorBackR = BLACK_COLOR_R;
            colorBackG = BLACK_COLOR_G;
            colorBackB = BLACK_COLOR_B;
            break;
        case GameResult::BLACK_WIN:
            text = "BLACK WINS";
            colorFontR = BLACK_COLOR_R;
            colorFontG = BLACK_COLOR_G;
            colorFontB = BLACK_COLOR_B;
            colorBackR = WHITE_COLOR_R;
            colorBackG = WHITE_COLOR_G;
            colorBackB = WHITE_COLOR_B;
            break;
        case GameResult::DRAW_RESULT:
            text = "DRAW";
            colorFontR = BOARD_DARK_R;
            colorFontG = BOARD_DARK_G;
            colorFontB = BOARD_DARK_B;
            colorBackR = BOARD_LIGHT_R;
            colorBackG = BOARD_LIGHT_G;
            colorBackB = BOARD_LIGHT_B;
            break;
    }
    drawText(   m_renderer, END_GAME_TITLE_MIDDLE_X, END_GAME_TITLE_MIDDLE_Y,
                text, m_font_name, MAIN_MENU_TITLE_FONT_SIZE, colorFontR, colorFontG, colorFontB,
                colorBackR, colorBackG, colorBackB);

    drawAuthor(colorFontR, colorFontG, colorFontB, colorBackR, colorBackG, colorBackB);

}

void EndGameView::drawBackground() {
    Uint8 colorR = 0;
    Uint8 colorG = 0;
    Uint8 colorB = 0;
    switch (m_gameResult) {
        case GameResult::WHITE_WIN:
            colorR = BLACK_COLOR_R;
            colorG = BLACK_COLOR_G;
            colorB = BLACK_COLOR_B;
            break;
        case GameResult::BLACK_WIN:
            colorR = WHITE_COLOR_R;
            colorG = WHITE_COLOR_G;
            colorB = WHITE_COLOR_B;
            break;
        case GameResult::DRAW_RESULT:
            colorR = BOARD_LIGHT_R;
            colorG = BOARD_LIGHT_G;
            colorB = BOARD_LIGHT_B;
            break;
    }
    SDL_SetRenderDrawColor( m_renderer, colorR, colorG, colorB, 0xFF );
    SDL_RenderClear( m_renderer );
}

WhichViewNext EndGameView::run() {
    bool quit = false; //main loop flag
    SDL_Event e; //event handler

    //draw everything on board
    drawBackground();
    setButtons();
    drawResult();

    //prepare variable in which will be set the next view
    WhichViewNext returnValue = WhichViewNext::DEFAULT_VALUE;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
                returnValue = WhichViewNext::EXIT;
            }
            //button to go to main menu
            if (m_buttons[0].handleEvent(&e)) {
                quit = true;
                returnValue = WhichViewNext::MAIN_MENU;
            }
            //button to exit program
            if (m_buttons[1].handleEvent(&e)) {
                quit = true;
                returnValue = WhichViewNext::EXIT;
            }
            //update screen
            SDL_RenderPresent(m_renderer);
        }

    }
    return returnValue;
}