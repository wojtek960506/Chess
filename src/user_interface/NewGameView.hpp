#ifndef NEWGAME_HPP
#define NEWGAME_HPP

#include <vector>

#include "BaseView.hpp"
#include "DrawBoardRect.hpp"
#include "../main_logic/Game.hpp"
#include "../rules/Move.hpp"
#include "SDL_Button.hpp"
#include "BoardFieldButton.hpp"
#include "../main_logic/SaveState.hpp"

/**
 * class represents the view of the game in the app
 */
class NewGameView : public BaseView {
public:
    NewGameView(SDL_Renderer * renderer, Game * game); // : BaseView(renderer), m_game(game) {}
    WhichViewNext run() override;
private:
    void drawMainBoard();
    void drawSurrounding(unsigned int fieldSize, unsigned int fontSize, unsigned int beginX, unsigned int beginY);
    void drawPlayerTurn();
    void setBoardButtons(unsigned int fieldSize, unsigned int beginX, unsigned int beginY);
    void setFunctionalButtons();
    void deleteBoardButtons();
    void markSpecialFieldsBeforeMove(const int & numPos, const int & letPos, bool & moveFigureFlag);
    bool doMovement(const int & numPos, const int & letPos, bool & moveFigureFlag);

    bool executeMovement(const int & numPos, const int & letPos, bool & moveFigureFlag);
    void executePromotion();
    bool executeCheck();

    void doNormalMove(const int & figColor, const int & figType, const int & numPosBefore, const int & letPosBefore, const int & numPosAfter, const int & letPosAfter);
    void doCastleMove(const int & numPosBefore, const int & letPosBefore, const int & numPosAfter, const int & letPosAfter);
    void doEnPassant(const int & numPosBefore, const int & letPosBefore, const int & numPosAfter, const int & letPosAfter);
    void redrawNormalField(const int & numPos, const int & letPos);
    void redrawFigure(const int & numPos, const int & letPos);
    void drawCheckFields();
    void undrawCheckFields();

    void clearMarksAfterMovement();
    void changeTurn();
    void disallowEnPassant();

    //bool checkIfClickedOutsideFieldsToMove(const int & numPos, const int & letPos);

    vector<vector<DrawBoardRect>> m_boardFields;
    vector<BoardFieldButton> m_boardButtons;
    vector<SDL_Button> m_functionalButtons;

    //vector<pair<int,int>> m_checkFields;
    Game * m_game;
};

#endif //NEWGAME_HPP
