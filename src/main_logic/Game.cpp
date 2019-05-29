#include "Game.hpp"

#include <cstdlib>

using namespace std;

/**
 * function to add figure to the set of figures stored in the game
 * @param figure figure to add
 */
void Game::addFigure(Figure * figure) {
    int tmpNumPos = figure->getNumPos();
    int tmpLetPos = figure->getLetPos();

    //add figure to set of figures and place it on board
    m_figures.insert(figure);
    m_board->putFigure(figure,tmpNumPos, tmpLetPos);

    //current figure is the figure which we have just added, because we add figure only when there is promotion
    m_currentFigure = figure;
}

/**
 * function to set of figures stored in the game on the board
 */
void Game::setFiguresOnBoard() {
    for (const auto & f : m_figures) {
        int tmp_rank = f->getNumPos(); //row
        int tmp_file = f->getLetPos(); //column
        m_board->putFigure(f, tmp_rank, tmp_file);
    }
}

/**
 * copy constructor of class Game
 * @param game
 */
Game::Game(const Game & game) {
    for (const FieldToMove & fieldToMove : game.m_fieldsToMove) m_fieldsToMove.push_back(fieldToMove);
    for (const pair<int,int> & checkField : game.m_checkFields) m_checkFields.push_back(checkField);
    m_currentFigure = game.m_currentFigure;
    m_playerWhite = game.m_playerWhite;
    m_playerBlack  = game.m_playerBlack;
    m_gameResult = game.m_gameResult;
    m_whiteKing = game.m_whiteKing;
    m_blackKing = game.m_blackKing;
    //for (const Figure* figure : game.m_figures) m_figures.insert(figure->clone());
    for (Figure* figure : game.m_figures) m_figures.insert(figure);
    m_board = game.m_board;
    m_currentPlayer = game.m_currentPlayer;
}

/**
 * operator of assignment for class Game
 * @param game
 * @return
 */
Game & Game::operator = (const Game & game) {
    if (this == &game) return *this;

    //first destruct
    for (auto m_figure : m_figures) {
        delete m_figure;
    }
    delete m_board;
    m_figures.clear();
    m_currentFigure = nullptr;
    m_whiteKing = nullptr;
    m_blackKing = nullptr;

    //then create
    for (const FieldToMove & fieldToMove : game.m_fieldsToMove) m_fieldsToMove.push_back(fieldToMove);
    for (const pair<int,int> & checkField : game.m_checkFields) m_checkFields.push_back(checkField);
    m_currentFigure = game.m_currentFigure;
    m_playerWhite = game.m_playerWhite;
    m_playerBlack  = game.m_playerBlack;
    m_gameResult = game.m_gameResult;
    m_whiteKing = game.m_whiteKing;
    m_blackKing = game.m_blackKing;
    //for (const Figure* figure : game.m_figures) m_figures.insert(figure->clone());
    for (Figure* figure : game.m_figures) m_figures.insert(figure);
    m_board = game.m_board;
    m_currentPlayer = game.m_currentPlayer;

    return *this;
}


/**
 * constructor to create the standard game from the very beginning state
 * @param playerWhite
 * @param playerBlack
 */
Game::Game(PlayerType playerWhite, PlayerType playerBlack) {
    //set types of players
    m_playerWhite = playerWhite;
    m_playerBlack = playerBlack;
    //-----------------------------------------------------------------------------------------------------------------
    //set all figures
	for (unsigned int i = 0 ; i < BOARD_SIZE ; ++i) {
		m_figures.insert(new Pawn(FigureColor::BLACK, 1, i));
		m_figures.insert(new Pawn(FigureColor::WHITE, 6, i));
		switch (i) {
			case 0:
			case 7:
				m_figures.insert(new Rook(FigureColor::BLACK, 0, i));
				m_figures.insert(new Rook(FigureColor::WHITE, 7, i));
				break;
			case 1:
			case 6:
			    m_figures.insert(new Knight(FigureColor::BLACK, 0, i));
				m_figures.insert(new Knight(FigureColor::WHITE, 7, i));
				break;
			case 2:
			case 5:
				m_figures.insert(new Bishop(FigureColor::BLACK, 0, i));
				m_figures.insert(new Bishop(FigureColor::WHITE, 7, i));
				break;
			case 3:
				m_figures.insert(new Queen(FigureColor::BLACK, 0, i));
				m_figures.insert(new Queen(FigureColor::WHITE, 7, i));
				break;
			case 4:
				m_figures.insert(new King(FigureColor::BLACK, 0, i));
				m_figures.insert(new King(FigureColor::WHITE, 7, i));
				break;
			default:
				break;
		}
	}

	//add figures to board
    m_board = new Board();
	setFiguresOnBoard();

	m_currentPlayer = FigureColor::WHITE;

	//keep the information about both kings
	m_whiteKing = dynamic_cast<King*>(m_board->getFigureAtPos(7,4));
	m_blackKing = dynamic_cast<King*>(m_board->getFigureAtPos(0,4));
}

/**
 * constructor to create the game in the given state. It sets all necessary arguments to set game to valid state
 * @param currentPlayer
 * @param players
 * @param figures
 * @param whiteKingCoord
 * @param blackKingCoord
 */
Game::Game(const FigureColor & currentPlayer, const pair<PlayerType, PlayerType> & players, const set<Figure*> & figures,
     const pair<int,int> & whiteKingCoord, const pair<int,int> & blackKingCoord) {
    //set informations about players
    m_currentPlayer = currentPlayer;
    m_playerWhite = players.first;
    m_playerBlack = players.second;
    //copy all figures into game's set of figures
    for (const auto & figure : figures) m_figures.insert(figure);
    //create board and place figures there
    m_board = new Board();
    setFiguresOnBoard();
    //save pointers to both kings
    m_whiteKing = dynamic_cast<King*>(m_board->getFigureAtPos(whiteKingCoord.first, whiteKingCoord.second));
    m_blackKing = dynamic_cast<King*>(m_board->getFigureAtPos(blackKingCoord.first, blackKingCoord.second));
}

/**
 * function of simple AI to randomly choose figure to move
 * @return return the chosen figure
 */
Figure * Game::chooseFigureForAI() {
    set<Figure*> figuresTmp; //we can choose only from our color
    for (const auto & figure : m_figures) {
        if (figure->getFigColor() == m_currentPlayer) {
            figuresTmp.insert(figure);
        }
    }

    int size = figuresTmp.size(); //number of figures
    int randomIndex = rand() % size; //trivial random numbers in C style are enough

    auto it = figuresTmp.begin();
    for (int i = 0 ; i < randomIndex ; ++i) ++it; //move iterator to the index which was randomly selected

    return *it; //return figure which was selected
}

/**
 * function of simple AI to choose the move for the chosen figure
 * @return return the field to make capture or in case of no such chance then some random (but valid) field
 */
pair<int,int> Game::chooseFieldToMoveForAI() {
    //choose capture
    for (const auto & fieldToMove : m_fieldsToMove) {
        if (fieldToMove.getMoveType() == MoveType::CAPTURE) return make_pair(fieldToMove.getNumPos(), fieldToMove.getLetPos());
    }

    //there was no capture so random move
    int size = m_fieldsToMove.size();
    int randomIndex = rand() % size;

    auto it = m_fieldsToMove.begin();
    for (int i = 0 ; i < randomIndex ; ++i) ++it; //move iterator to the index which was randomly selected

    return make_pair(it->getNumPos(), it->getLetPos());
}

/**
 * function for simple AI to randomly choose to which figure pawn is promoted
 * @return return the new figure type
 */
FigureType Game::choosePromotionForAI() {
    int randomIndex = rand() % 4; //there are four types of figures to promote

    FigureType returnValue = FigureType::NONE_T;
    switch (randomIndex) {
        case 0:
            returnValue = FigureType::QUEEN;
            break;
        case 1:
            returnValue = FigureType::ROOK;
            break;
        case 2:
            returnValue = FigureType::KNIGHT;
            break;
        case 3:
            returnValue = FigureType::BISHOP;
            break;
        default:
            returnValue = FigureType::NONE_T;
            break;
    }
    return returnValue;
}

/**
 * function to detect if the current player is represented by AI
 * @return
 */
bool Game::checkIfCurrentPlayerIsAI() const {
    if (m_currentPlayer == FigureColor::WHITE) {
        if (m_playerWhite == PlayerType::COMPUTER) return true; //current player is computer
        else return false; //current player is normal player
    } else { //current player is black
        if (m_playerBlack == PlayerType::COMPUTER) return true;
        else return false;
    }
}

/**
 * destructor of the class Game
 */
Game::~Game() {
	for (auto m_figure : m_figures) {
		delete m_figure;
	}
    delete m_board;
	m_figures.clear();
	m_currentFigure = nullptr;
	m_whiteKing = nullptr;
	m_blackKing = nullptr;
}

/**
 * function to change the current player after evaluating its movement
 */
void Game::changeTurn() {
    if (m_currentPlayer == FigureColor::WHITE) m_currentPlayer = FigureColor::BLACK;
    else m_currentPlayer = FigureColor::WHITE;
}

/**
 * function to automatically set oppent as a winner
 */
void Game::resign() {
    if (m_currentPlayer == FigureColor::WHITE) m_gameResult = GameResult::BLACK_WIN;
    else m_gameResult = GameResult::WHITE_WIN;
}

/**
 * function to print the board
 */
void Game::printBoard() {
    vector<vector<Figure*>> boardArray = m_board->getBoardArray();
    for (const auto & a : boardArray) {
        for (const auto & p : a) {
            if (p == nullptr) cout << -1 << " ";
            else cout << *p << " ";
        }
        cout << endl;
    }
}