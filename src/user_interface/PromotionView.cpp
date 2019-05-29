#include "PromotionView.hpp"



PromotionView::PromotionView(SDL_Renderer *renderer, FigureColor figureColor) : m_renderer(renderer), m_figureColor(figureColor) {
    setButtons();
}

void PromotionView::setButtons() {
    int buttonSize = 216;

    //top left button (queen)
    m_buttons.push_back(BoardFieldButton(108, 216, buttonSize, buttonSize, 0,0));
    //top right button (rook)
    m_buttons.push_back(BoardFieldButton(396, 216, buttonSize, buttonSize,0,0));
    //bottom left button (knight)
    m_buttons.push_back(BoardFieldButton(108, 468, buttonSize, buttonSize,0,0));
    //bottom left button (bishop)
    m_buttons.push_back(BoardFieldButton(396, 468, buttonSize, buttonSize,0,0));
}

void PromotionView::clearBackground() {
    drawFilledRect(m_renderer, SCREEN_HEIGHT, SCREEN_HEIGHT, BOARD_SURR_BEGIN_X, BOARD_SURR_BEGIN_Y,
             PROMOTION_BACKGROUND_R, PROMOTION_BACKGROUND_G, PROMOTION_BACKGROUND_B);
}

void PromotionView::drawTitle() {

    //for CLion
    //const char * font = "../src/fonts/OpenSans-Bold.ttf";

    //for makefile
    //const char * font = "./src/fonts/OpenSans-Bold.ttf";

    //const char * font = CHESS_FONT_FILE;

    drawText(   m_renderer, PROMOTION_FONT_MIDDLE_X, PROMOTION_FONT_MIDDLE_Y, "PROMOTION", m_font_name, PROMOTION_FONT_SIZE,
                PROMOTION_FONT_R, PROMOTION_FONT_G, PROMOTION_FONT_B,
                PROMOTION_BACKGROUND_R, PROMOTION_BACKGROUND_G, PROMOTION_BACKGROUND_B);
}

void PromotionView::drawFiguresToChoose() {
    //set images of figures to choose
    DrawBoardRect * queen = new DrawBoardRect(m_renderer, BoardRectColor::LIGHT,
            PROMOTION_QUEEN_POS_X, PROMOTION_QUEEN_POS_Y,
            m_figureColor, FigureType::QUEEN, RectSurrColor::NONE_S, true,
            PROMOTION_IMAGE_SIZE, PROMOTION_IMAGE_SIZE);
    DrawBoardRect * rook = new DrawBoardRect(m_renderer, BoardRectColor::LIGHT,
            PROMOTION_ROOK_POS_X, PROMOTION_ROOK_POS_Y,
            m_figureColor, FigureType::ROOK, RectSurrColor::NONE_S, true,
            PROMOTION_IMAGE_SIZE, PROMOTION_IMAGE_SIZE);
    DrawBoardRect * knight = new DrawBoardRect(m_renderer, BoardRectColor::LIGHT,
            PROMOTION_KNIGHT_POS_X, PROMOTION_KNIGHT_POS_Y,
            m_figureColor, FigureType::KNIGHT, RectSurrColor::NONE_S, true,
            PROMOTION_IMAGE_SIZE, PROMOTION_IMAGE_SIZE);
    DrawBoardRect * bishop = new DrawBoardRect(m_renderer, BoardRectColor::LIGHT,
            PROMOTION_BISHOP_POS_X, PROMOTION_BISHOP_POS_Y,
            m_figureColor, FigureType::BISHOP, RectSurrColor::NONE_S, true,
            PROMOTION_IMAGE_SIZE, PROMOTION_IMAGE_SIZE);
    //draw images
    queen->draw();
    rook->draw();
    knight->draw();
    bishop->draw();
    //free allocated memory
    delete queen;
    delete rook;
    delete knight;
    delete bishop;
}

FigureType PromotionView::run() {
    FigureType returnValue = FigureType::NONE_T;
    bool quit = false; //main loop flag
    SDL_Event e; //event handler

    //clear the background for promotion view
    clearBackground();
    //draw title and figures to choose
    drawTitle();
    drawFiguresToChoose();
    //update view
    SDL_RenderPresent( m_renderer );

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
                returnValue = FigureType::NONE_T;
            }

            //check if any button was clicked
            for (unsigned int i = 0 ; i < 4 ; ++i) {
                if (m_buttons[i].handleEvent(&e)) {
                    switch(i) {
                        case 0:
                            quit = true;
                            returnValue = FigureType::QUEEN;
                            break;
                        case 1:
                            quit = true;
                            returnValue = FigureType::ROOK;
                            break;
                        case 2:
                            quit = true;
                            returnValue = FigureType::KNIGHT;
                            break;
                        case 3:
                            quit = true;
                            returnValue = FigureType::BISHOP;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    //return figure to which the pawn is promoted. In case of closing program in this stage return FigureType::NONE_T
    return returnValue;
}
