#ifndef GAME_HPP
#define GAME_HPP

#include <set>

#include "../figures/Figure.hpp"
#include "Board.hpp"

using namespace std;

class Figure;
class King;

/**
 * Class to represent the main game. It stores the most important values to evaluate the game in current state.
 */
class Game {
public:
	Game(PlayerType playerWhite, PlayerType playerBlack); //default beginning of the game
    Game(const Game & game);
    Game & operator = (const Game & game);
    Game * clone() { return new Game(*this); }
	Game(const FigureColor & currentPlayer, const pair<PlayerType, PlayerType> & players, const set<Figure*> & figures,
         const pair<int,int> & whiteKingCoord, const pair<int,int> & blackKingCoord);
	~Game();
    Board * getBoardPtr() const { return m_board; }
    void setFiguresOnBoard();
	void printBoard();
    set<Figure*> * getFiguresPtr() { return &m_figures; }

    void resign();



    //--------------------------------------------------------------------------------------------------------------
    //at some point I will have to repair this concept

    //I want free access to those fields
    vector<FieldToMove> m_fieldsToMove; //this container is used to store what are the possible movements of the current figure
    vector<pair<int,int>> m_checkFields;    //this container is used to store coordinates of the king which is checked
                                            //as well as figure(s) which attack him

    Figure * m_currentFigure = nullptr;
    PlayerType m_playerWhite;
    PlayerType m_playerBlack;
    GameResult m_gameResult = GameResult::DRAW_RESULT;

    //--------------------------------------------------------------------------------------------------------------

    bool checkIfCurrentPlayerIsAI() const;
    FigureColor getCurrentPlayer() const { return m_currentPlayer; }
    King * getWhiteKing() const { return m_whiteKing; }
    King * getBlackKing() const { return m_blackKing; }
    void changeTurn();
    void addFigure(Figure * figure);
    PlayerType getPlayerWhite() const { return m_playerWhite; }
    PlayerType getPlayerBlack() const { return m_playerBlack; }
    const vector<pair<int,int>> & getCheckFields() const { return m_checkFields; }

    Figure * chooseFigureForAI();
    pair<int,int> chooseFieldToMoveForAI();
    FigureType choosePromotionForAI();

private:
    King * m_whiteKing;
    King * m_blackKing;
    set<Figure*> m_figures;
	Board * m_board;
    FigureColor m_currentPlayer;
};

#endif //GAME_HPP