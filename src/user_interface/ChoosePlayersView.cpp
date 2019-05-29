#include "ChoosePlayersView.hpp"
#include "DrawBoardRect.hpp"

void ChoosePlayersView::setButtons() {

    //white player button
    m_buttons.push_back(SDL_Button( CHOOSE_PLAYER_WHITE_BUTTON_X, CHOOSE_PLAYER_WHITE_BUTTON_Y,
                                    CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT));
    drawFilledRect( m_renderer, CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT,
                    CHOOSE_PLAYER_WHITE_BUTTON_X, CHOOSE_PLAYER_WHITE_BUTTON_Y,
                    CHOOSE_PLAYER_BACKGROUND_R, CHOOSE_PLAYER_BACKGROUND_G, CHOOSE_PLAYER_BACKGROUND_B);

    //black player button
    m_buttons.push_back(SDL_Button( CHOOSE_PLAYER_BLACK_BUTTON_X, CHOOSE_PLAYER_BLACK_BUTTON_Y,
                                    CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT));
    drawFilledRect( m_renderer, CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT,
                    CHOOSE_PLAYER_BLACK_BUTTON_X, CHOOSE_PLAYER_BLACK_BUTTON_Y,
                    CHOOSE_PLAYER_BACKGROUND_R, CHOOSE_PLAYER_BACKGROUND_G, CHOOSE_PLAYER_BACKGROUND_B);

    //start game button
    m_buttons.push_back(SDL_Button( CHOOSE_PLAYER_START_BUTTON_X, CHOOSE_PLAYER_START_BUTTON_Y,
                                    CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT));
    drawFilledRect( m_renderer, CHOOSE_PLAYER_START_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT,
                    CHOOSE_PLAYER_START_BUTTON_X, CHOOSE_PLAYER_START_BUTTON_Y,
                    CHOOSE_PLAYER_BACKGROUND_R, CHOOSE_PLAYER_BACKGROUND_G, CHOOSE_PLAYER_BACKGROUND_B);
}

void ChoosePlayersView::drawTitle() {
    drawText(   m_renderer, CHOOSE_PLAYER_TITLE_FONT_MIDDLE_X, CHOOSE_PLAYER_TITLE_FONT_MIDDLE_Y, "CHOOSE PLAYERS",
                m_font_name, CHOOSE_PLAYER_FONT_SIZE * 4 / 3,
                MAIN_MENU_TITLE_FONT_R, MAIN_MENU_TITLE_FONT_G, MAIN_MENU_TITLE_FONT_B,
                MAIN_MENU_BACKGROUND_R, MAIN_MENU_BACKGROUND_G, MAIN_MENU_BACKGROUND_B);



    //the same position as in main menu, so I will keep everything
    /*drawText(   m_renderer, SCREEN_WIDTH-135, SCREEN_HEIGHT-MAIN_MENU_AUTHOR_FONT_SIZE, "Author: Wojciech Zielinski",
                m_font_name, MAIN_MENU_AUTHOR_FONT_SIZE,
                MAIN_MENU_AUTHOR_FONT_R, MAIN_MENU_AUTHOR_FONT_G, MAIN_MENU_AUTHOR_FONT_B,
                MAIN_MENU_BACKGROUND_R, MAIN_MENU_BACKGROUND_G, MAIN_MENU_BACKGROUND_B);
    */
    drawAuthor();

    redrawPlayerWhite();
    redrawPlayerBlack();

    //start button
    drawText(   m_renderer, CHOOSE_PLAYER_START_FONT_MIDDLE_X, CHOOSE_PLAYER_START_FONT_MIDDLE_Y, "START GAME",
                m_font_name, CHOOSE_PLAYER_FONT_SIZE,
                CHOOSE_PLAYER_FONT_R, CHOOSE_PLAYER_FONT_G, CHOOSE_PLAYER_FONT_B,
                CHOOSE_PLAYER_BACKGROUND_R, CHOOSE_PLAYER_BACKGROUND_G, CHOOSE_PLAYER_BACKGROUND_B);


}

void ChoosePlayersView::drawImages() {
    //set images of figures to choose
    DrawBoardRect * white = new DrawBoardRect(m_renderer, BoardRectColor::LIGHT,
                                              CHOOSE_PLAYER_WHITE_IMAGE_X, CHOOSE_PLAYER_WHITE_IMAGE_Y,
                                              FigureColor::WHITE, FigureType::PAWN, RectSurrColor::NONE_S, false,
                                              CHOOSE_PLAYER_IMAGE_SIZE, CHOOSE_PLAYER_IMAGE_SIZE);
    DrawBoardRect * black = new DrawBoardRect(m_renderer, BoardRectColor::LIGHT,
                                              CHOOSE_PLAYER_BLACK_IMAGE_X, CHOOSE_PLAYER_BLACK_IMAGE_Y,
                                              FigureColor::BLACK, FigureType::PAWN, RectSurrColor::NONE_S, false,
                                              CHOOSE_PLAYER_IMAGE_SIZE, CHOOSE_PLAYER_IMAGE_SIZE);
    //draw images
    white->draw();
    black->draw();
    //free allocated memory
    delete white;
    delete black;
}

void ChoosePlayersView::redrawPlayerWhite() {
    drawFilledRect( m_renderer, CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT,
                    CHOOSE_PLAYER_WHITE_BUTTON_X, CHOOSE_PLAYER_WHITE_BUTTON_Y,
                    CHOOSE_PLAYER_BACKGROUND_R, CHOOSE_PLAYER_BACKGROUND_G, CHOOSE_PLAYER_BACKGROUND_B);

    const char * player;
    if (m_playerWhite == PlayerType::NORMAL_PLAYER) player = "NORMAL";
    else player = "COMPUTER";
    drawText(   m_renderer, CHOOSE_PLAYER_WHITE_FONT_MIDDLE_X, CHOOSE_PLAYER_WHITE_FONT_MIDDLE_Y, player, m_font_name,
                CHOOSE_PLAYER_FONT_SIZE,
                CHOOSE_PLAYER_FONT_R, CHOOSE_PLAYER_FONT_G, CHOOSE_PLAYER_FONT_B,
                CHOOSE_PLAYER_BACKGROUND_R, CHOOSE_PLAYER_BACKGROUND_G, CHOOSE_PLAYER_BACKGROUND_B);
}

void ChoosePlayersView::redrawPlayerBlack() {
    drawFilledRect( m_renderer, CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT,
                    CHOOSE_PLAYER_BLACK_BUTTON_X, CHOOSE_PLAYER_BLACK_BUTTON_Y,
                    CHOOSE_PLAYER_BACKGROUND_R, CHOOSE_PLAYER_BACKGROUND_G, CHOOSE_PLAYER_BACKGROUND_B);

    const char * player;
    if (m_playerBlack == PlayerType::NORMAL_PLAYER) player = "NORMAL";
    else player = "COMPUTER";
    drawText(   m_renderer, CHOOSE_PLAYER_BLACK_FONT_MIDDLE_X, CHOOSE_PLAYER_BLACK_FONT_MIDDLE_Y, player, m_font_name,
                CHOOSE_PLAYER_FONT_SIZE,
                CHOOSE_PLAYER_FONT_R, CHOOSE_PLAYER_FONT_G, CHOOSE_PLAYER_FONT_B,
                CHOOSE_PLAYER_BACKGROUND_R, CHOOSE_PLAYER_BACKGROUND_G, CHOOSE_PLAYER_BACKGROUND_B);
}

void ChoosePlayersView::changePlayerWhite() {
    if (m_playerWhite == PlayerType::NORMAL_PLAYER) m_playerWhite = PlayerType::COMPUTER;
    else m_playerWhite = PlayerType::NORMAL_PLAYER;
}

void ChoosePlayersView::changePlayerBlack() {
    if (m_playerBlack == PlayerType::NORMAL_PLAYER) m_playerBlack = PlayerType::COMPUTER;
    else m_playerBlack = PlayerType::NORMAL_PLAYER;
}

WhichViewNext ChoosePlayersView::run() {
    bool quit = false; //main loop flag
    SDL_Event e; //event handler

    SDL_SetRenderDrawColor( m_renderer, MAIN_MENU_BACKGROUND_R, MAIN_MENU_BACKGROUND_G, MAIN_MENU_BACKGROUND_B, 0xFF );
    SDL_RenderClear( m_renderer );

    //draw everything on board
    setButtons();
    drawTitle();
    drawImages();

    WhichViewNext returnValue = WhichViewNext::DEFAULT_VALUE;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
                returnValue = WhichViewNext::EXIT;
            }
            //button for player with white figures
            if (m_buttons[0].handleEvent(&e)) {
                changePlayerWhite();
                redrawPlayerWhite();
            }
            //button for player with black figures
            if (m_buttons[1].handleEvent(&e)) {
                changePlayerBlack();
                redrawPlayerBlack();
            }
            //button to start game
            if (m_buttons[2].handleEvent(&e)) {
                quit = true;
                returnValue = WhichViewNext::NEW_GAME;
            }
            //update screen
            SDL_RenderPresent(m_renderer);
        }
    }
    return returnValue;

}

