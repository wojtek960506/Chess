#include <sstream>
#include "NewGameView.hpp"
#include "../rules/Check.hpp"
#include "../rules/Checkmate.hpp"
#include "../rules/Promotion.hpp"
#include "../rules/Stalemate.hpp"
#include "PromotionView.hpp"
#include <exception>
#include <time.h>

class PromotionFail : public exception {};

NewGameView::NewGameView(SDL_Renderer * renderer, Game * game) : BaseView(renderer), m_game(game) {

    //board fields
    for (unsigned int i = 0 ; i < BOARD_SIZE ; ++i) {
        vector <DrawBoardRect> tmp;
        for (unsigned int j = 0 ; j < BOARD_SIZE ; ++j) {
            Figure * figure = m_game->getBoardPtr()->getFigureAtPos(i, j);
            FigureColor figColor;
            FigureType  figType;
            if (figure == nullptr) {
                figColor = FigureColor::NONE_C;
                figType = FigureType::NONE_T;
            } else {
                figColor = (FigureColor) figure->getFigColor();
                figType = (FigureType) figure->getFigType();
            }
            BoardRectColor rectColor;
            if ((i+j)%2==0) rectColor = BoardRectColor::LIGHT;
            else rectColor = BoardRectColor::DARK;
            int beginX = BOARD_BEGIN_X + (BOARD_FIELD_SIZE*j);
            int beginY = BOARD_BEGIN_Y + (BOARD_FIELD_SIZE*i);
            RectSurrColor surr = RectSurrColor::NONE_S;
            bool marked = false;
            tmp.push_back(DrawBoardRect(m_renderer, rectColor, beginX, beginY, figColor, figType, surr, marked));
        }
        m_boardFields.push_back(tmp);
    }
    setBoardButtons(BOARD_FIELD_SIZE, BOARD_BEGIN_X, BOARD_BEGIN_Y);
}

void NewGameView::setFunctionalButtons() {
    //exit button
    int MBV = 10; //move buttons vertically

    drawFilledRect(m_renderer, SCREEN_WIDTH - SCREEN_HEIGHT, 100, SCREEN_HEIGHT, SCREEN_HEIGHT - 150 + MBV,
            MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);

    drawText(m_renderer,
             SCREEN_HEIGHT + (SCREEN_WIDTH-SCREEN_HEIGHT)/2,
             SCREEN_HEIGHT - 100 + MBV,
             "EXIT", m_font_name, 50,
             MAIN_MENU_BUTTON_FONT_R ,MAIN_MENU_BUTTON_FONT_G, MAIN_MENU_BUTTON_FONT_B,
             MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);

    //add exit button
    m_functionalButtons.push_back(SDL_Button(SCREEN_HEIGHT, SCREEN_HEIGHT - 150 + MBV, SCREEN_WIDTH - SCREEN_HEIGHT, 100));

    //------------------------------------------------------------------------------------------------------------------

    //main menu button
    drawFilledRect(m_renderer, SCREEN_WIDTH - SCREEN_HEIGHT, 100, SCREEN_HEIGHT, SCREEN_HEIGHT - 275 + MBV,
            MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);

    drawText(m_renderer,
             SCREEN_HEIGHT + (SCREEN_WIDTH-SCREEN_HEIGHT)/2,
             SCREEN_HEIGHT - 225 + MBV,
             "MAIN MENU", m_font_name, 50,
             MAIN_MENU_BUTTON_FONT_R ,MAIN_MENU_BUTTON_FONT_G, MAIN_MENU_BUTTON_FONT_B,
             MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);

    //add main menu button
    m_functionalButtons.push_back(SDL_Button(SCREEN_HEIGHT, SCREEN_HEIGHT - 275 + MBV, SCREEN_WIDTH - SCREEN_HEIGHT, 100));

    //------------------------------------------------------------------------------------------------------------------

    //save state button
    drawFilledRect(m_renderer, SCREEN_WIDTH - SCREEN_HEIGHT, 100, SCREEN_HEIGHT, SCREEN_HEIGHT - 400 + MBV,
            MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);

    drawText(m_renderer,
             SCREEN_HEIGHT + (SCREEN_WIDTH-SCREEN_HEIGHT)/2,
             SCREEN_HEIGHT - 350 + MBV,
             "SAVE STATE", m_font_name, 50,
             MAIN_MENU_BUTTON_FONT_R ,MAIN_MENU_BUTTON_FONT_G, MAIN_MENU_BUTTON_FONT_B,
             MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);
    //add save state button
    m_functionalButtons.push_back(SDL_Button(SCREEN_HEIGHT, SCREEN_HEIGHT - 400 + MBV, SCREEN_WIDTH - SCREEN_HEIGHT, 100));

    //------------------------------------------------------------------------------------------------------------------

    //resign button
    drawFilledRect(m_renderer, SCREEN_WIDTH - SCREEN_HEIGHT, 100, SCREEN_HEIGHT, SCREEN_HEIGHT - 525 + MBV,
            MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);

    drawText(m_renderer,
             SCREEN_HEIGHT + (SCREEN_WIDTH-SCREEN_HEIGHT)/2,
             SCREEN_HEIGHT - 475 + MBV,
             "RESIGN", m_font_name, 50,
             MAIN_MENU_BUTTON_FONT_R ,MAIN_MENU_BUTTON_FONT_G, MAIN_MENU_BUTTON_FONT_B,
             MAIN_MENU_BUTTON_BACKGROUND_R, MAIN_MENU_BUTTON_BACKGROUND_G, MAIN_MENU_BUTTON_BACKGROUND_B);
    //resign button
    m_functionalButtons.push_back(SDL_Button(SCREEN_HEIGHT, SCREEN_HEIGHT - 525 + MBV, SCREEN_WIDTH - SCREEN_HEIGHT, 100));
}

void NewGameView::markSpecialFieldsBeforeMove(const int & numPos, const int & letPos, bool & moveFigureFlag) {
    m_game->m_fieldsToMove.clear();
    m_game->m_currentFigure = m_game->getBoardPtr()->getFigureAtPos(numPos, letPos);

    //there is no figure on this field or player wanted to choose the oponent's figure
    if (m_game->m_currentFigure == nullptr || m_game->m_currentFigure->getFigColor() != m_game->getCurrentPlayer()) {
        moveFigureFlag = false;
        return;
    }
    if (m_game->m_currentFigure->getFigColor() == FigureColor::WHITE)
        m_game->m_fieldsToMove = m_game->m_currentFigure->getFullRangeOfMoves(m_game->getWhiteKing(), m_game->getBoardPtr());
    else //FigureColor::BLACK
        m_game->m_fieldsToMove = m_game->m_currentFigure->getFullRangeOfMoves(m_game->getBlackKing(), m_game->getBoardPtr());

    //redraw the field on which the figure is standing
    m_boardFields[m_game->m_currentFigure->getNumPos()][m_game->m_currentFigure->getLetPos()].setMarked(true);
    m_boardFields[m_game->m_currentFigure->getNumPos()][m_game->m_currentFigure->getLetPos()].draw();

    //redraw fields where the player can move the figure
    for (const auto & fieldToMove : m_game->m_fieldsToMove) {
        int tmpNumPos = fieldToMove.getNumPos();
        int tmpLetPos = fieldToMove.getLetPos();
        MoveType moveType = fieldToMove.getMoveType();
        RectSurrColor rectSurrColor = RectSurrColor::NONE_S;

        //according to the type of the move there is different color frame on a field
        switch (moveType) {
            case MoveType::NORMAL:
                rectSurrColor = RectSurrColor::MOVE_S;
                break;
            case MoveType::CAPTURE:
            case MoveType::EN_PASSANT:
                rectSurrColor = RectSurrColor::CAPTURE_S;
                break;
            case MoveType::CASTLE:
                rectSurrColor = RectSurrColor::CASTLE_S;
                break;
            case MoveType::CHECK:
                rectSurrColor = RectSurrColor::CHECK_S;
                break;
            default:
                continue;
        }
        m_boardFields[tmpNumPos][tmpLetPos].setSurr((rectSurrColor));
        m_boardFields[tmpNumPos][tmpLetPos].draw();
    }
    moveFigureFlag = true;
}

//change turn of the player
void NewGameView::changeTurn() {
    //if (m_game->m_currentPlayer == FigureColor::WHITE) m_game->m_currentPlayer = FigureColor::BLACK;
    //else m_game->m_currentPlayer = FigureColor::WHITE;
    m_game->changeTurn();
    drawPlayerTurn();
}

//after movement we have to get rid of marks of possibility of movement
void NewGameView::clearMarksAfterMovement() {
    for (const auto & fieldToMove : m_game->m_fieldsToMove) {
        m_boardFields[fieldToMove.getNumPos()][fieldToMove.getLetPos()].setSurr(RectSurrColor::NONE_S);
        m_boardFields[fieldToMove.getNumPos()][fieldToMove.getLetPos()].draw();
    }
    m_game->m_fieldsToMove.clear();
    if (m_game->m_currentFigure != nullptr) { //here we are only when the move was not fine
        m_boardFields[m_game->m_currentFigure->getNumPos()][m_game->m_currentFigure->getLetPos()].setMarked(false);
        m_boardFields[m_game->m_currentFigure->getNumPos()][m_game->m_currentFigure->getLetPos()].draw();
        m_game->m_currentFigure = nullptr;
    }
}

//en passant can be done only just after the movement of the pawn which can be captured with en passant
void NewGameView::disallowEnPassant() {
    for (auto & figure : *m_game->getFiguresPtr()) {
        //we can do en passant only in first move after the pawn moved of two fields forward
        if (figure->getFigType() == FigureType::PAWN && figure->getFigColor() != m_game->m_currentFigure->getFigColor()) {
            dynamic_cast<Pawn*>(figure)->disallowEnPassant();
        }
    }
}

//redraw fields after move of a figure (it can be move with capture of without)
void NewGameView::doNormalMove(const int & figColor, const int & figType, const int & numPosBefore,
        const int & letPosBefore, const int & numPosAfter, const int & letPosAfter) {
    //update the field where the figure was before movement
    redrawNormalField(numPosBefore, letPosBefore);

    //update the field where the figure was moved
    m_boardFields[numPosAfter][letPosAfter].setFigColor((FigureColor)figColor);
    m_boardFields[numPosAfter][letPosAfter].setFigType((FigureType)figType);
    m_boardFields[numPosAfter][letPosAfter].draw();
}

//redraw king and rook after castling
void NewGameView::doCastleMove(const int & numPosBefore, const int & letPosBefore, const int & numPosAfter, const int & letPosAfter) {
    //arguments are positions for king ; based on them I will calculate positions for rook
    int rookNumPos = numPosBefore, oldRookLetPos, newRookLetPos; //rook is on the same rank as king after castling
    if (letPosAfter > LetterPosition::LET_POS_E) { //right side castling
        oldRookLetPos = LetterPosition::LET_POS_H;
        newRookLetPos = LetterPosition::LET_POS_F;
    } else { //left side castling
        oldRookLetPos = LetterPosition::LET_POS_A;
        newRookLetPos = LetterPosition::LET_POS_D;
    }
    //redraw rook
    doNormalMove(m_game->m_currentFigure->getFigColor(), FigureType::ROOK, rookNumPos, oldRookLetPos, rookNumPos, newRookLetPos);
    //redraw king
    doNormalMove(m_game->m_currentFigure->getFigColor(), m_game->m_currentFigure->getFigType(), numPosBefore, letPosBefore, numPosAfter, letPosAfter);

}

//get rid of figure image from the field
void NewGameView::redrawNormalField(const int & numPos, const int & letPos) {
    m_boardFields[numPos][letPos].setFigColor(FigureColor::NONE_C);
    m_boardFields[numPos][letPos].setFigType(FigureType::NONE_T);
    m_boardFields[numPos][letPos].setMarked(false);
    m_boardFields[numPos][letPos].draw();
}

//it is used to redraw figure on field. Mainly just for promotion
void NewGameView::redrawFigure(const int & numPos, const int & letPos) {
    m_boardFields[numPos][letPos].setFigColor((FigureColor)m_game->m_currentFigure->getFigColor());
    m_boardFields[numPos][letPos].setFigType((FigureType)m_game->m_currentFigure->getFigType());
    m_boardFields[numPos][letPos].draw();
}

//redraw fields after the en passant movement
void NewGameView::doEnPassant(const int & numPosBefore, const int & letPosBefore, const int & numPosAfter, const int & letPosAfter) {
    //redraw the offensive pawn
    doNormalMove(m_game->m_currentFigure->getFigColor(), m_game->m_currentFigure->getFigType(),
            numPosBefore, letPosBefore, numPosAfter, letPosAfter);
    //redraw field with captured pawn
    int captNumPos = numPosBefore;
    int captLetPos = letPosAfter;
    redrawNormalField(captNumPos, captLetPos);
}

//change background of the fields which take part in castling to the red color
void NewGameView::drawCheckFields() {
    for (const auto & field : m_game->m_checkFields) {
        m_boardFields[field.first][field.second].setChecked(true);
        m_boardFields[field.first][field.second].draw();
    }
}

//when the check is over change color of fields to its normal state
void NewGameView::undrawCheckFields() {
    for (const auto & field : m_game->m_checkFields) {
        m_boardFields[field.first][field.second].setChecked(false);
        m_boardFields[field.first][field.second].draw();
    }
}

//checks if the promotion can be done and executes it
//this function can throw PromotionFail if we will close the program during the promotion
void NewGameView::executePromotion() {
    //check if the promotion of pawn can be done
    Promotion promotion (m_game->getBoardPtr(), m_game->m_currentFigure);
    //when the promotion can be done show the screen to choose new figure
    if (promotion.check()) {

        //just to make sure that those buttons will not affect chossing the promotion figure
        deleteBoardButtons();

        //simple algorithm for AI
        if (m_game->checkIfCurrentPlayerIsAI()) {
            //randomly choose promoted figure
            FigureType promotionType = m_game->choosePromotionForAI();
            //redraw figure
            promotion.promotePawn(m_game, promotionType);

            //set board buttons once again as they were deleted before selecting the promotion
            setBoardButtons(BOARD_FIELD_SIZE, BOARD_BEGIN_X, BOARD_BEGIN_Y);

            redrawFigure(m_game->m_currentFigure->getNumPos(), m_game->m_currentFigure->getLetPos());
            SDL_RenderPresent( m_renderer );

        } else { //show promotion screen for normal player
            PromotionView promotionView(m_renderer, (FigureColor)m_game->m_currentFigure->getFigColor());
            FigureType promotionType = promotionView.run();

            //there was exit while promotion
            if (promotionType == FigureType::NONE_T) {
                throw PromotionFail();
            }
            //delete pawn from figures and add new figure to which pawn was promoted
            promotion.promotePawn(m_game, promotionType);

            redrawFigure(m_game->m_currentFigure->getNumPos(), m_game->m_currentFigure->getLetPos());

            //redraw board and set back board buttons
            drawSurrounding(BOARD_FIELD_SIZE, BOARD_FONT_SIZE, BOARD_SURR_BEGIN_X, BOARD_SURR_BEGIN_Y);
            drawMainBoard();
            setBoardButtons(BOARD_FIELD_SIZE, BOARD_BEGIN_X, BOARD_BEGIN_Y);
            SDL_RenderPresent( m_renderer );
        }
    }
}

//redraw current players check fields and check if the next player will be checked
//it returns true if the next player is checkmated which terminates the game
bool NewGameView::executeCheck() {
    //get king to check check position
    King * king;
    if (m_game->getCurrentPlayer() == FigureColor::WHITE) {
        king = m_game->getBlackKing();
    } else {
        king = m_game->getWhiteKing();
    }

    //get rid of fields which informed about check
    undrawCheckFields();
    m_game->m_checkFields.clear();

    //check if the opponent's king is checked after the move
    Check check (m_game->getBoardPtr(), king);
    if (check.check()) {
        //mark fields which attack king
        for (const auto & attackFigure : check.getAttackFigures())
            m_game->m_checkFields.push_back(make_pair(attackFigure->getNumPos(), attackFigure->getLetPos()));

        //mark king
        m_game->m_checkFields.push_back(make_pair(king->getNumPos(), king->getLetPos()));

        Checkmate checkmate (m_game->getBoardPtr(), king, check.getAttackFigures());
        if (checkmate.check()) { //if there is a checkmate then return true to finish game
            //set the winner of the game
            if (m_game->getCurrentPlayer() == FigureColor::WHITE) m_game->m_gameResult = GameResult::WHITE_WIN;
            else m_game->m_gameResult = GameResult::BLACK_WIN;
            return true;
        }
    } else { //check stalemate
        //check stalemate
        Stalemate stalemate (m_game->getBoardPtr(), m_game);
        //if there is a stalemate we finish game with a draw
        if (stalemate.check()) {
            //quit = true;
            m_game->m_gameResult = GameResult::DRAW_RESULT;
            return true;
        }
    }
    return false;
}


//executes movement
bool NewGameView::executeMovement(const int & numPos, const int & letPos, bool & moveFigureFlag) {
    //class move is responsible to check if the movement is possible
    Move move( m_game->getBoardPtr(), m_game, m_game->m_currentFigure, m_game->getFiguresPtr(),
                            m_game->m_fieldsToMove, numPos, letPos);
    //if the move was done update figures on board
    int numPosBefore = m_game->m_currentFigure->getNumPos();
    int letPosBefore = m_game->m_currentFigure->getLetPos();

    //if the move is not possible then we don't change the player
    //at this point move will not be done if we click into the field which is not included inside possible fields to move
    //actual movement is done inside the check function

    //TODO after every capture reset pointer on field (actually moves are done inside this check function)
    if (move.check()) {
        switch (move.getMoveType()) {
            case MoveType::NORMAL:
            case MoveType::CAPTURE:
                doNormalMove(m_game->m_currentFigure->getFigColor(), m_game->m_currentFigure->getFigType(),
                             numPosBefore, letPosBefore, numPos, letPos);
                break;
            case MoveType::EN_PASSANT:
                doEnPassant(numPosBefore, letPosBefore, numPos, letPos);
                break;
            case MoveType::CASTLE:
                doCastleMove(numPosBefore, letPosBefore, numPos, letPos);
                break;
            default:
                break;
        }

        //check if there is time for pawn promotion (move is passed to free memory in case of earlier termination)
        executePromotion();

        //redraw field
        if (executeCheck()) return true;

        //there was no checkmate after, so change player and redraw fields of check
        changeTurn(); //move was fine so we change the player
        drawCheckFields();
        disallowEnPassant(); //if the en passant was not done immediately then disallow it
    }

    moveFigureFlag = false; //even if the move was not fine then we still have to start this process from beginning
    clearMarksAfterMovement();

    return false; //there was no checkmate or stalemate after movement
}

//try to do movement based on the field chosen by player
bool NewGameView::doMovement(const int & numPos, const int & letPos, bool & moveFigureFlag) {
    bool returnValue = false; //it is more likely that after a single move there will be no checkmate
    //cancel the move with this figure if we click on it
    if ((numPos == m_game->m_currentFigure->getNumPos() && letPos == m_game->m_currentFigure->getLetPos())) {
        clearMarksAfterMovement();
        moveFigureFlag = false;
    } else { //execute movement
        returnValue = executeMovement(numPos, letPos, moveFigureFlag);
    }
    m_game->m_currentFigure = nullptr;
    return returnValue; //there was no checkmate
}

WhichViewNext NewGameView::run() {

    cout << endl << "BOARD AT THE BEGINNING" << endl;
    m_game->printBoard();
    cout << endl;

    bool moveFigureFlag = false;
    bool quit = false; //main loop flag
    SDL_Event e; //event handler

    SDL_SetRenderDrawColor( m_renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( m_renderer );
    drawSurrounding(BOARD_FIELD_SIZE, BOARD_FONT_SIZE, BOARD_SURR_BEGIN_X, BOARD_SURR_BEGIN_Y);
    drawMainBoard();
    drawPlayerTurn();
    setFunctionalButtons();
    SDL_RenderPresent( m_renderer );

    WhichViewNext returnValue = WhichViewNext::DEFAULT_VALUE;
    int count = 0;
    while (!quit) {
        count++;
        //do AI movement
        if (m_game->checkIfCurrentPlayerIsAI()) {

            //SIMPLE AI ALGORITHM

            //when the current figure cannot move, we have to choose different one
            while (true) {
                //clear fields to move from the previous movement
                m_game->m_fieldsToMove.clear();

                //choose figure to move
                Figure *figureToMove = m_game->chooseFigureForAI();
                m_game->m_currentFigure = figureToMove;


                //get all possible moves for this figure
                if (m_game->m_currentFigure->getFigColor() == FigureColor::WHITE)
                    m_game->m_fieldsToMove = m_game->m_currentFigure->getFullRangeOfMoves(m_game->getWhiteKing(),
                                                                                          m_game->getBoardPtr());
                else //FigureColor::BLACK
                    m_game->m_fieldsToMove = m_game->m_currentFigure->getFullRangeOfMoves(m_game->getBlackKing(),
                                                                                          m_game->getBoardPtr());

                //choose place to move of this figure
                if (m_game->m_fieldsToMove.size() == 0) { //if there is no movement for the chosen figure, then choose different one
                    m_game->m_currentFigure = nullptr;
                    continue;
                }

                //redraw the field on which the figure is standing
                m_boardFields[m_game->m_currentFigure->getNumPos()][m_game->m_currentFigure->getLetPos()].setMarked(true);
                m_boardFields[m_game->m_currentFigure->getNumPos()][m_game->m_currentFigure->getLetPos()].draw();

                pair<int,int> chosenFieldToMove = m_game->chooseFieldToMoveForAI();

                try {
                    //if there was a mate finish the game
                    if (doMovement(chosenFieldToMove.first, chosenFieldToMove.second, moveFigureFlag)) {
                        quit = true;
                        returnValue = WhichViewNext::END_GAME;
                        return returnValue;
                    }
                } catch (const PromotionFail &e) {
                    //there was exit while promotion
                    quit = true;
                    returnValue = WhichViewNext::EXIT;
                }
                SDL_RenderPresent( m_renderer );

                break;

            }
        }

        //handle mouse events (including movement of normal player)
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
                returnValue = WhichViewNext::EXIT;
            }

            //check if any button on board was clicked
            for (auto & boardButton : m_boardButtons) {

                //handle mouse clicks on board
                if (boardButton.handleEvent(&e)) {
                    if (m_game->checkIfCurrentPlayerIsAI()) { //we cannot move with clicks when it is AI's movement
                        cout << "AI" << endl;
                        continue;
                    } else { //execute clicks of normal player
                        if (moveFigureFlag == false) { //show where I can move
                            markSpecialFieldsBeforeMove(boardButton.getNumPos(), boardButton.getLetPos(), moveFigureFlag);
                        } else { //do movement
                            try {
                                //if there was a mate finish the game
                                if (doMovement(boardButton.getNumPos(), boardButton.getLetPos(), moveFigureFlag)) {
                                    quit = true;
                                    returnValue = WhichViewNext::END_GAME;
                                }
                            } catch (const PromotionFail &e) {
                                //there was exit while promotion
                                quit = true;
                                returnValue = WhichViewNext::EXIT;
                            }
                        }
                    }

                }
            }

            //check if any functional button was clicked
            //exit application
            if (m_functionalButtons[0].handleEvent(&e)) {
                quit = true;
                returnValue = WhichViewNext::EXIT;
            }

            //go back to main menu
            if (m_functionalButtons[1].handleEvent(&e)) {
                quit = true;
                returnValue = WhichViewNext::MAIN_MENU;
            }

            //save state
            if (m_functionalButtons[2].handleEvent(&e)) {
                string fileName = FILE_WITH_STATE_NAME;

                string fileNameWithDir = FILES_WITH_STATES_DIR + fileName + FILE_WITH_STATE_EXTENSION;

                SaveState saveState(fileNameWithDir);

                if (saveState.saveStateToFile(m_game)) {
                    cout << "State was successfully saved to file: |" << fileNameWithDir  << "|" << endl;
                } else {
                    cout << "Cannot save state to file: |" << fileNameWithDir << "|" << endl;
                }


                cout << "save state" << endl;
            }

            //resign state
            if (m_functionalButtons[3].handleEvent(&e)) {
                //when there is AI's move we cannot resign
                if (!m_game->checkIfCurrentPlayerIsAI()) {
                    m_game->resign();
                    quit = true;
                    returnValue = WhichViewNext::END_GAME;

                }
            }

            //update screen
            SDL_RenderPresent( m_renderer );
        }
    }

    cout << endl << "BOARD AT THE END" << endl;
    m_game->printBoard();
    cout << endl;

    return returnValue;
}

void NewGameView::drawMainBoard() {
    for (auto & file : m_boardFields) { //file is a chess name for column
        for (auto & field : file) {
            field.draw();
        }
    }
    drawAuthor();
}

void NewGameView::drawPlayerTurn() {
    drawFilledRect( m_renderer, SCREEN_WIDTH - SCREEN_HEIGHT, 2 * PLAYER_TURN_FONT_SIZE, SCREEN_HEIGHT, 0,
                    PLAYER_TURN_BACKGROUND_R, PLAYER_TURN_BACKGROUND_G, PLAYER_TURN_BACKGROUND_B);

    if (m_game->getCurrentPlayer() == FigureColor::WHITE) {
        drawText(   m_renderer, PLAYER_TURN_FONT_MIDDLE_X, PLAYER_TURN_FONT_MIDDLE_Y, "WHITE", m_font_name, PLAYER_TURN_FONT_SIZE,
                    WHITE_TURN_FONT_R, WHITE_TURN_FONT_G, WHITE_TURN_FONT_B,
                    PLAYER_TURN_BACKGROUND_R, PLAYER_TURN_BACKGROUND_G, PLAYER_TURN_BACKGROUND_B);
    }
    else {
        drawText(   m_renderer, PLAYER_TURN_FONT_MIDDLE_X, PLAYER_TURN_FONT_MIDDLE_Y, "BLACK", m_font_name, PLAYER_TURN_FONT_SIZE,
                    BLACK_TURN_FONT_R, BLACK_TURN_FONT_G, BLACK_TURN_FONT_B,
                    PLAYER_TURN_BACKGROUND_R, PLAYER_TURN_BACKGROUND_G, PLAYER_TURN_BACKGROUND_B);
    }
}

//set all buttons representing board //size of button , beginX of board, beginY of board
void NewGameView::setBoardButtons(unsigned int fieldSize, unsigned int beginX, unsigned int beginY) {
    for (unsigned int i = 0 ; i < BOARD_SIZE ; ++i) {
        for (unsigned int j = 0 ; j < BOARD_SIZE ; ++j) {
            m_boardButtons.push_back(BoardFieldButton(beginX + j * fieldSize, beginY + i * fieldSize, fieldSize, fieldSize,i,j));
        }
    }
}

//it is used before choosing figure to promotion
void NewGameView::deleteBoardButtons() {
    m_boardButtons.clear();
}


string uIntToString(const unsigned int & num) {
    string out_string;
    stringstream ss;
    ss << num;
    out_string = ss.str();
    return out_string;
}

string charToString(const char & c) {
    string str;
    stringstream ss;
    ss << c;
    ss >> str;
    return str;
}


void NewGameView::drawSurrounding(unsigned int fieldSize, unsigned int fontSize, unsigned int beginX, unsigned int beginY) {
    drawFilledRect(m_renderer, fieldSize/2, SCREEN_HEIGHT, beginX, beginY,
            BOARD_SURROUNDING_R, BOARD_SURROUNDING_G, BOARD_SURROUNDING_B);
    drawFilledRect(m_renderer, SCREEN_HEIGHT, fieldSize/2, beginX, beginY,
            BOARD_SURROUNDING_R, BOARD_SURROUNDING_G, BOARD_SURROUNDING_B);
    drawFilledRect(m_renderer, fieldSize/2, SCREEN_HEIGHT, beginX+SCREEN_HEIGHT-fieldSize/2, beginY,
            BOARD_SURROUNDING_R, BOARD_SURROUNDING_G, BOARD_SURROUNDING_B);
    drawFilledRect(m_renderer, SCREEN_HEIGHT, fieldSize/2, beginX, beginY+SCREEN_HEIGHT-fieldSize/2,
            BOARD_SURROUNDING_R, BOARD_SURROUNDING_G, BOARD_SURROUNDING_B);

    for (unsigned int i = 0 ; i < BOARD_SIZE ; ++i) {
        string tmpNum = uIntToString(BOARD_SIZE-i);
        string tmpChar = charToString(i+65); //A is 65 in decimal in ASCII

        drawText(m_renderer,
                 beginX + fieldSize/4,
                 beginY + fieldSize + fieldSize*i,
                 tmpNum.c_str(), m_font_name, fontSize,
                 BOARD_FONT_R, BOARD_FONT_G, BOARD_FONT_B,
                 BOARD_SURROUNDING_R, BOARD_SURROUNDING_G, BOARD_SURROUNDING_B);

        drawText(m_renderer,
                 beginX + fieldSize/4 + fieldSize*(BOARD_SIZE) + fieldSize/2,
                 beginY + fieldSize + fieldSize*i,
                 tmpNum.c_str(), m_font_name, fontSize,
                 BOARD_FONT_R, BOARD_FONT_G, BOARD_FONT_B,
                 BOARD_SURROUNDING_R, BOARD_SURROUNDING_G, BOARD_SURROUNDING_B);

        drawText(m_renderer,
                 beginX + fieldSize + fieldSize*i,
                 beginY + fieldSize/4,
                 tmpChar.c_str(), m_font_name, fontSize,
                 BOARD_FONT_R, BOARD_FONT_G, BOARD_FONT_B,
                 BOARD_SURROUNDING_R, BOARD_SURROUNDING_G, BOARD_SURROUNDING_B);

        drawText(m_renderer,
                 beginX + fieldSize + fieldSize*i,
                 beginY + fieldSize/4 + fieldSize*(BOARD_SIZE) + fieldSize/2,
                 tmpChar.c_str(), m_font_name, fontSize,
                 BOARD_FONT_R, BOARD_FONT_G, BOARD_FONT_B,
                 BOARD_SURROUNDING_R, BOARD_SURROUNDING_G, BOARD_SURROUNDING_B);
    }
}
