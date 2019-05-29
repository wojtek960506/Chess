#include "SaveState.hpp"

using namespace std;

/**
 * function to save the single figure to the file
 * @param file - file to which we are saving
 * @param figure - figure to be saved
 * @return true in case of success; false in case of some problem with figure
 */
bool SaveState::saveFigure (fstream & file, const Figure * figure) {
    //save color of figure
    if (figure->getFigColor() == FigureColor::WHITE) file << 'W' << ' ';
    else if (figure->getFigColor() == FigureColor::BLACK) file << 'B' << ' ';
    else return false;

    //save position of figure
    if (figure->getNumPos() < 0 || figure->getNumPos() > 7) return false;
    else file << figure->getNumPos() << ' ';
    if (figure->getLetPos() < 0 || figure->getLetPos() > 7) return false;
    else file << figure->getLetPos() << ' ';

    //save number of moves of figure
    file << figure->getMoves();

    return true;
}

/**
 * function to save all figures currently in the game to the file
 * @param file - file to which we are saving
 * @param game - pointer to teh game from which we take figures
 * @return
 */
bool SaveState::saveFigures(fstream & file, Game * game) {
    file << "FIGURES" << '\n';

    for (const Figure* figure : *game->getFiguresPtr()) {
        switch (figure->getFigType()) {
            case FigureType::PAWN:
                file << 'P' << ' ';
                saveFigure(file, figure);
                file << ' ';
                if (dynamic_cast<const Pawn*>(figure)->canBeCapturedWithEnPassant()) file << 'T';
                else file << 'F';
                file << '\n';
                break;
            case FigureType::ROOK:
                file << 'R' << ' ';
                saveFigure(file, figure);
                file << '\n';
                break;
            case FigureType::KNIGHT:
                file << 'N' << ' ';
                saveFigure(file, figure);
                file << '\n';
                break;
            case FigureType::BISHOP:
                file << 'B' << ' ';
                saveFigure(file, figure);
                file << '\n';
                break;
            case FigureType::QUEEN:
                file << 'Q' << ' ';
                saveFigure(file, figure);
                file << '\n';
                break;
            case FigureType::KING:
                file << 'K' << ' ';
                saveFigure(file, figure);
                file << '\n';
                break;
            default:
                return false;

        }
    }

    file << "END" << '\n';
    return true;
}

/**
 * main function to save the state to the file; name of the file is given
 * @param game - game from which we are saving
 * @return true in case of success ; false in case of some failure
 */
bool SaveState::saveStateToFile(Game *game) {
    fstream file;
    file.open(m_filename, fstream::out);
    if (file.is_open()) {
        int whiteKingNumPos;
        int whiteKingLetPos;
        int blackKingNumPos;
        int blackKingLetPos;
        char currentPlayer;
        char whitePlayerType;
        char blackPlayerType;


        //save position of white king
        if (game->getWhiteKing() != nullptr) {
            whiteKingNumPos = game->getWhiteKing()->getNumPos();
            whiteKingLetPos = game->getWhiteKing()->getLetPos();
        } else
            return false;

        //save position of black king
        if (game->getWhiteKing() != nullptr) {
            blackKingNumPos = game->getBlackKing()->getNumPos();
            blackKingLetPos = game->getBlackKing()->getLetPos();
        } else
            return false;

        //save current player
        if (game->getCurrentPlayer() == FigureColor::WHITE) currentPlayer = 'W';
        else if (game->getCurrentPlayer() == FigureColor::BLACK) currentPlayer = 'B';
        else {
            file.close();
            return false;
        }

        //save types of players
        if (game->getPlayerWhite() == PlayerType::NORMAL_PLAYER) whitePlayerType = 'N';
        else if (game->getPlayerWhite() == PlayerType::COMPUTER) whitePlayerType = 'C';
        else {
            file.close();
            return false;
        }
        if (game->getPlayerBlack() == PlayerType::NORMAL_PLAYER) blackPlayerType = 'N';
        else if (game->getPlayerBlack() == PlayerType::COMPUTER) blackPlayerType = 'C';
        else {
            file.close();
            return false;
        }


        file << whiteKingNumPos << ' ' << whiteKingLetPos << '\n';
        file << blackKingNumPos << ' ' << blackKingLetPos << '\n';
        file << currentPlayer << '\n';
        file << whitePlayerType << ' ' << blackPlayerType << '\n';
        file << "FTC" << '\n'; //Fields To Check
        for (const pair<int,int> & checkField : game->getCheckFields()) {
            file << checkField.first << ' ' << checkField.second << '\n';
        }

        //save all informations about figures
        if (!saveFigures(file, game)) {
            file.close();
            return false;
        }

        file.close(); //after reading all informations to the file, close it and return true
        return true;
    }

    //file was not successfully open, so we have to return false
    return false;
}
