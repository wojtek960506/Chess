#include "CheckAttacksOnField.hpp"
#include "EnPassant.hpp"

/**
 * function to check if there is a figure on diagonal which attacks the field
 * those figure can be quenn, bishop, king or pawn (but king (in case of no check after it) and pawn only from the closest range)
 * @param numPos - numerical position of the field
 * @param letPos  - letter position of the field
 * @param diagonal - direction of the diagonal representent by a pair of signed numbers
 * @return true in case of possibility to attack; false otherwise
 */
bool CheckAttacksOnField::checkDiagonal(const int & numPos, const int & letPos, const pair<int,int> & diagonal) {
    int tmpNumPos = numPos + diagonal.first;
    int tmpLetPos = letPos + diagonal.second;
    bool first = true; //to check pawns and king
    try {
        while(true) {
            //get the figure on the current field to check if it attacks
            Figure * figure = m_board->getFigureAtPos(tmpNumPos, tmpLetPos);

            //the field is empty
            if (figure == nullptr) {
                tmpNumPos += diagonal.first; tmpLetPos += diagonal.second; first = false; continue;
            }
            //there is figure with the current move color on the current field
            if (figure->getFigColor() == m_figureColor) {

                //king cannot block field from attack because then king is attacked
                if (figure->getFigType() == FigureType::KING) {
                    tmpNumPos += diagonal.first; tmpLetPos += diagonal.second; first = false; continue;
                }

                return false; //there is no attack from our figure
            }

            /*if (m_figure != nullptr && figure->getFigColor() == m_figure->getFigColor()) {
                return false; //there is no attack from our figure
            }*/


            //check pawns and king (they have affect on diagonal if they are close)
            if (first) {
                //check king
                if (figure->getFigType() == FigureType::KING && !m_check) {
                    m_attackFigures.push_back(figure);
                    return true;
                }
                //check pawns
                if (figure->getFigType() == FigureType::PAWN) {
                    if (diagonal.first < 0) {
                        if (figure->getFigColor() == FigureColor::BLACK) {
                            m_attackFigures.push_back(figure);
                            return true;
                        }
                    } else {
                        if (figure->getFigColor() == FigureColor::WHITE) {
                            m_attackFigures.push_back(figure);
                            return true;
                        }
                    }
                }
                first = false;
            } //else {
            // check other figures
                //check bishop and queen
                if (figure->getFigType() == FigureType::BISHOP || figure->getFigType() == FigureType::QUEEN) {
                    m_attackFigures.push_back(figure);
                    return true;
                } else { //only bishop and queen can affect on long attack from diagonal
                    return false;
                }
            //}
        }
    } catch (const InvalidPosition & e) {
        return false;
    }
}

//returns true if there is a figure on any diagonal which attacks the field
/**
 * function to check if there is a figure on any diagonal which attacks the given field
 * @param numPos - numeric position of the field
 * @param letPos - letter position of the field
 * @return true in case of possibility to attack; false otherwise
 */
bool CheckAttacksOnField::checkDiagonals(const int & numPos, const int & letPos) {
    int diagonals[2] = {1,-1};
    vector<pair<int,int>> allDiagonals;
    for (int i : diagonals) for (int j : diagonals) allDiagonals.emplace_back(i,j);
    for (pair<int,int> diagonal : allDiagonals) {
        if (checkDiagonal(numPos, letPos, diagonal)) return true;
    }
    return false;
}

/**
 * function to check if there is a figure on a given rank which attacks the field
 * those figures can be queen, rook, king or pawn (with en passant) (but king(in case of no check after it) and pawn only from the closest range)
 * @param numPos - numeric position of the field
 * @param letPos - letter position of the field
 * @param rankOrFile - direction of the rank or file represent by pair of two numbers (one of them is 0)
 * @return true in case of possibility ot attack; false otherwise
 */
bool CheckAttacksOnField::checkRankOrFile(const int & numPos, const int & letPos, const pair<int,int> & rankOrFile) {
    int tmpNumPos = numPos + rankOrFile.first;
    int tmpLetPos = letPos + rankOrFile.second;
    bool first = true; //to check the king
    try {
        while (true) {
            //get the figure on the current field to check if it attacks
            Figure * figure = m_board->getFigureAtPos(tmpNumPos, tmpLetPos);

            //the field is empty
            if (figure == nullptr) {
                tmpNumPos += rankOrFile.first; tmpLetPos += rankOrFile.second; first = false; continue;
            }

            //there is figure with the current move color on the current field
            if (figure->getFigColor() == m_figureColor) {

                //king cannot block field from attack because then king is attacked
                if (figure->getFigType() == FigureType::KING) {
                    tmpNumPos += rankOrFile.first; tmpLetPos += rankOrFile.second; first = false; continue;
                }

                return false; //there is no attack from our figure
            }

            /*
            if (m_figure != nullptr && figure->getFigColor() == m_figure->getFigColor()) {
                return false; //there is no attack from our figure
            }*/


            //check king and en passant
            if (first) {
                if (figure->getFigType() == FigureType::KING && !m_check) {
                    m_attackFigures.push_back(figure);
                    return true;
                }
                //check en passant
                if (figure->getFigType() == FigureType::PAWN) {
                    if (EnPassant(m_board, figure, EnPassantSide::EN_LEFT).check()) return true;
                    if (EnPassant(m_board, figure, EnPassantSide::EN_RIGHT).check()) return true;
                }
                first = false;
            }
            //else {
             //check other figures
                //check queen and rook
                if (figure->getFigType() == FigureType::QUEEN || figure->getFigType() == FigureType::ROOK) {
                    m_attackFigures.push_back(figure);
                    return true;
                } else { //only queen and rook can affect on long attack from rank or file
                    return false;
                }
            //}
        }
    } catch (const InvalidPosition & e) {
        return false;
    }
}

//returns true if there is a figure on any rank(row) or file(column) which attacks the field
/**
 * function to check if there is a figure on any rank(row) or file(column) which attacks the given field
 * @param numPos - numeric position of the field
 * @param letPos - letter positino of the field
 * @return true in case of such possibility; false otherwise
 */
bool CheckAttacksOnField::checkRanksAndFiles(const int & numPos, const int & letPos) {
    int ranksAndFiles[2] = {1, -1};
    vector<pair<int,int>> allRanksAndFiles;
    for (int i : ranksAndFiles) { allRanksAndFiles.emplace_back(i, 0); allRanksAndFiles.emplace_back(0, i);  }
    for (pair<int,int> rankOrFile : allRanksAndFiles) {
        if (checkRankOrFile(numPos, letPos, rankOrFile)) return true;
    }
    return false;
}

/**
 * function to check if the knight which attacks the given field
 * @param numPos - numeric position of the field
 * @param letPos - letter positio of the field
 * @param knightPos - position of the knight represented as a pair of two numbers
 * @return true in case of possibility to attack; false otherwise
 */
bool CheckAttacksOnField::checkKnight(const int & numPos, const int & letPos, const pair<int,int> & knightPos) {
    int tmpNumPos = numPos + knightPos.first;
    int tmpLetPos = letPos + knightPos.second;
    try {
        Figure * figure = m_board->getFigureAtPos(tmpNumPos, tmpLetPos);

        //check if there is figure with the current move color on the current field
        if(figure == nullptr || figure->getFigColor() == m_figureColor) {
            return false; //there is no attack from our figure
        }

        //if (figure == nullptr || (m_figure != nullptr && figure->getFigColor() == m_figure->getFigColor())) return false;


        if (figure->getFigType() == FigureType::KNIGHT) {
            m_attackFigures.push_back(figure);
            return true;
        } else
            return false;
    } catch (const InvalidPosition & e) {
        return false;
    }
}

/**
 * function to check if there is any knight which attacks the given field
 * @param numPos - numeric position of the field
 * @param letPos - letter positio of the field
 * @return true in case of possibility to attack; false otherwise
 */
bool CheckAttacksOnField::checkKnights(const int & numPos, const int & letPos) {
    int pos1[2] = {1,-1};
    int pos2[2] = {2,-2};
    vector<pair<int,int>> allKnightPos;
    for (int i : pos1) for (int j : pos2) { allKnightPos.push_back(make_pair(i,j)); allKnightPos.push_back(make_pair(j,i)); }
    for (pair<int, int> knightPos : allKnightPos) {
        if (checkKnight(numPos, letPos, knightPos)) return true;
    }
    return false;
}

//returns true if there is any figure which attacks the field
/**
 * main function to check if there is any figure which attacks the given field (its coordinates are class members)
 * @return true in case of possibility to attack; false otherwise
 */
bool CheckAttacksOnField::check() {
    //on diagonals
    bool returnValue = false;

    if (checkDiagonals(m_numPos, m_letPos)) {
        returnValue = true;
        //return true;
    }
    //on ranks and files
    if (checkRanksAndFiles(m_numPos, m_letPos)) {
        returnValue = true;
        //return true;
    }
    //check knights
    if (checkKnights(m_numPos, m_letPos)) {
        returnValue = true;
        //return true;
    }

    //there is no attack on this field
    return returnValue;
}