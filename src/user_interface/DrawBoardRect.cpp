#include "DrawBoardRect.hpp"

#include <string>



using namespace std;

void DrawBoardRect::draw() {
    Uint8 colR=0, colG=0, colB=0;

    //when the button with figure is clicked
    if (m_marked) drawFilledRect(m_renderer, m_width, m_height, m_beginX, m_beginY,
            BOARD_MARKED_R, BOARD_MARKED_G, BOARD_MARKED_B);
    else {
        if (m_checked) { //when the field is included in check
            drawFilledRect(m_renderer, m_width, m_height, m_beginX, m_beginY,
                    BOARD_CHECKED_R, BOARD_CHECKED_G, BOARD_CHECKED_B);
        } else { //normal color of field
            if (m_rectColor == BoardRectColor::LIGHT) {
                colR = BOARD_LIGHT_R;
                colG = BOARD_LIGHT_G;
                colB = BOARD_LIGHT_B;
            } else { //m_rectColor == BoardRectColor::DARK
                colR = BOARD_DARK_R;
                colG = BOARD_DARK_G;
                colB = BOARD_DARK_B;
            }
            drawFilledRect(m_renderer, m_width, m_height, m_beginX, m_beginY, colR, colG, colB);
        }
    }

    if (m_surr != RectSurrColor::NONE_S) {
        switch (m_surr) {
            case RectSurrColor::MOVE_S:
                colR = BOARD_SURR_MOVE_R; colG = BOARD_SURR_MOVE_G; colB = BOARD_SURR_MOVE_B;
                break;
            case RectSurrColor::CAPTURE_S:
                colR = BOARD_SURR_CAPTURE_R; colG = BOARD_SURR_CAPTURE_G; colB = BOARD_SURR_CAPTURE_B;
                break;
            case RectSurrColor::CASTLE_S:
                colR = BOARD_SURR_CASTLE_R; colG = BOARD_SURR_CASTLE_G; colB = BOARD_SURR_CASTLE_B;
                break;
            case RectSurrColor::CHECK_S:
                colR = BOARD_SURR_CHECK_R; colG = BOARD_SURR_CHECK_G; colB = BOARD_SURR_CHECK_B;
                break;
            case RectSurrColor::MATE_S:
                colR = BOARD_SURR_MATE_R; colG = BOARD_SURR_MATE_G; colB = BOARD_SURR_MATE_B;
                break;
            default:
                break;
        }
        //those minus and plus are here to make very little space between neighbour fields
        drawRect(m_renderer, m_width-2, m_height-2, m_beginX+1, m_beginY+1, colR, colG, colB, SURR_THICKNESS);
    }

    if (m_figColor != FigureColor::NONE_C && m_figType != FigureType::NONE_T) {
        drawFigure();
    }
}


string getFigureFileName(FigureColor figColor, FigureType figType) {
    string color = "";
    string type = "";
    string file_name = "";
    switch (figType) {
        case FigureType::PAWN:
            type = "pawn"; break;
        case FigureType::ROOK:
            type = "rook"; break;
        case FigureType::KNIGHT:
            type = "knight"; break;
        case FigureType::BISHOP:
            type = "bishop"; break;
        case FigureType::QUEEN:
            type = "queen"; break;
        case FigureType::KING:
            type = "king"; break;
        default:
            break;
    }
    switch (figColor) {
        case FigureColor::WHITE:
            color = "white"; break;
        case FigureColor ::BLACK:
            color = "black"; break;
        default:
            break;
    }
    file_name = type + "_" + color + ".png";
    return file_name;

}

//void drawImage ( SDL_Renderer* renderer, int width, int height, int beginX, int beginY, const char * image)

void DrawBoardRect::drawFigure() {
    //for CLion
    //string extension = "./src/chess_figures/";

    //for makefile
    //string extension = "./src/chess_figures/";

    //string extension = CHESS_IMAGE_DIRECTORY;

    string extension = m_extension + getFigureFileName(m_figColor, m_figType);
    drawImage(m_renderer, m_width, m_height, m_beginX, m_beginY, extension.c_str());
}


