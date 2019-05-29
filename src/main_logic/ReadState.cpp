#include "ReadState.hpp"

/**
 * function reads the single line representing the field to check; it updates the vector of field to check (when the king is checked)
 * @param checkField
 * @param checkFields
 * @return true in case of properly formatted line ; false in the other case
 */
bool ReadState::readFieldToCheck(const string & checkField, vector<pair<int,int>> & checkFields) {
    if (checkField.length() != 3) { return false; } //the format is |num let| where num and let are digits from <0,7>
    int num = (int)checkField[0];
    if (num < 0 || num > 7) return false;
    int let = (int)checkField[2];
    if (let < 0 || let > 7) return false;
    //add it to check fields
    checkFields.push_back(make_pair(num,let));
    return true;
}

/**
 * function reads the single line representing figure and it updates the set of figures
 * @param figure
 * @param figures
 * @return true in case of properly formatted line ; false in case of some failure
 */
bool ReadState::readFigure(const string & figure, set<Figure*> & figures) {
    char figureTypeChar;
    char figureColorChar;
    FigureColor figureColor;
    int numPos;
    int letPos;
    int moves;
    char pawnToBeCapturedWithEnPassantChar;
    bool pawnToBeCapturedWithEnPassant;

    if (figure.length() == 0) return false;
    figureTypeChar = figure[0];
    //pawn has additional information about en passant movement
    if (figureTypeChar == 'P') {
        if (figure.length() != 11) return false;
    } else {
        if (figure.length() != 9) return false;
    }

    //read color
    figureColorChar = figure[2];
    if (figureColorChar == 'W') figureColor = FigureColor::WHITE;
    else if (figureColorChar == 'B') figureColor = FigureColor::BLACK;
    else return false;

    //read position
    numPos = figure[4]-48;
    if (numPos < 0 || numPos > 7) return false;
    letPos = figure[6]-48;
    if (letPos < 0 || letPos > 7) return false;

    //read number of movements
    moves = (int)figure[8]-48;

    switch (figureTypeChar) {
        case 'P':
            pawnToBeCapturedWithEnPassantChar = figure[10];
            if (pawnToBeCapturedWithEnPassantChar == 'T') pawnToBeCapturedWithEnPassant = true;
            else if (pawnToBeCapturedWithEnPassantChar == 'F') pawnToBeCapturedWithEnPassant = false;
            else return false;
            //insert pawn
            figures.insert(new Pawn(figureColor, numPos, letPos, moves, pawnToBeCapturedWithEnPassant));
            break;
        case 'R':
            //insert rook
            figures.insert(new Rook(figureColor, numPos, letPos, moves));
            break;
        case 'N':
            //insert knight
            figures.insert(new Knight(figureColor, numPos, letPos, moves));
            break;
        case 'B':
            //insert bishop
            figures.insert(new Bishop(figureColor, numPos, letPos, moves));
            break;
        case 'Q':
            //insert queen
            figures.insert(new Queen(figureColor, numPos, letPos, moves));
            break;
        case 'K':
            //insert king
            figures.insert(new King(figureColor, numPos, letPos, moves));
            break;
        default:
            return false;
    }
    return true;
}

/**
 * main function to read the state from the file
 * @return true in case of success ; false in case of some error in formatting or incorrect value
 */
bool ReadState::readStateFromFile() {
    fstream file;
    file.open(m_filename, fstream::in);
    //check if the file was open successfully
    if (file.is_open()) {
        int whiteKingNumPos;
        int whiteKingLetPos;
        int blackKingNumPos;
        int blackKingLetPos;
        char currentPlayerChar;
        FigureColor currentPlayer;
        char whitePlayerTypeChar;
        PlayerType whitePlayerType;
        char blackPlayerTypeChar;
        PlayerType blackPlayerType;
        set<Figure*> figures;
        vector<pair<int,int>> checkFields;

        string tmpToSkip;

        //read white king
        file >> whiteKingNumPos >> whiteKingLetPos;

        //read black king
        file >> blackKingNumPos >> blackKingLetPos;

        if ((whiteKingNumPos == blackKingNumPos) && (whiteKingLetPos == blackKingLetPos)) { file.close(); return false; }

        //read current player color
        file >> currentPlayerChar;


        //if (!(currentPlayerChar == 'B' || currentPlayerChar == 'W')) { file.close(); return false; }
        if (currentPlayerChar == 'B') currentPlayer = FigureColor::BLACK;
        else if (currentPlayerChar == 'W') currentPlayer = FigureColor::WHITE;
        else { file.close(); return false; }

        //read players' types
        file >> whitePlayerTypeChar >> blackPlayerTypeChar;
        if (whitePlayerTypeChar == 'N') whitePlayerType = PlayerType::NORMAL_PLAYER;
        else if (whitePlayerTypeChar == 'C') whitePlayerType = PlayerType::COMPUTER;
        else { file.close(); return false; }
        if (blackPlayerTypeChar == 'N') blackPlayerType = PlayerType::NORMAL_PLAYER;
        else if (blackPlayerTypeChar == 'C') blackPlayerType = PlayerType::COMPUTER;
        else { file.close(); return false; }

        //if (!(whitePlayerTypeChar == 'N' || whitePlayerTypeChar == 'C')) { file.close(); return false; }
        //if (!(blackPlayerTypeChar == 'N' || blackPlayerTypeChar == 'C')) { file.close(); return false; }

        //read 'FTC' constant
        file >> tmpToSkip;
        if (tmpToSkip != "FTC") { file.close(); return false; }

        //read fields to check
        string checkField;
        getline(file, checkField); //read the endline from the previous line
        getline(file, checkField); //try to get first field to check
        while (checkField != "FIGURES") {
            //parse field to check and add to all fields to check
            if (!readFieldToCheck(checkField, checkFields)) return false;

            cout << checkField << endl;
            getline(file, checkField); //get next line

            //check if we didn't get the end of file
            if (file.eof()) { file.close(); cout << "end of file too early -> ERROR !" << endl; return false; }
        }

        string figure;
        getline(file, figure); //try to read first figure
        while (figure != "END") {
            //parse figure and add it to set of figures
            if (!readFigure(figure, figures)) return false;

            cout << figure << endl;
            getline(file, figure);

            //check if we didn't get the end of file
            if (file.eof()) { file.close(); cout << "end of file too early -> ERROR !" << endl; return false; }
        }

        //everything was fine -> create new game and close the file
        m_game = new Game(currentPlayer, make_pair(whitePlayerType, blackPlayerType), figures,
                make_pair(whiteKingNumPos, whiteKingLetPos), make_pair(blackKingNumPos, blackKingLetPos));
        file.close();
        return true;
    }


    //it was not possible to even open the file
    return false;
}
