#ifndef CHECKATTACKSONFIELD_HPP
#define CHECKATTACKSONFIELD_HPP

#include "../main_logic/Board.hpp"
#include "../figures/Figure.hpp"

/**
 * class to check if there exist any of the opponents figure which attacks the given field
 */
class CheckAttacksOnField {
public:
    CheckAttacksOnField(Board * board, FigureColor figureColor, const int & numPos, const int & letPos, bool check = false)
        : m_board(board), m_figureColor(figureColor), m_numPos(numPos), m_letPos(letPos), m_check(check) {}
    bool check();
    const vector<Figure*> & getAttackFigures() const { return m_attackFigures; }
private:
    Board * m_board;
    FigureColor m_figureColor;
    int m_numPos;
    int m_letPos;
    bool m_check; //it is only used when we are looking for the figure which can capture the figure which checks the king
                  //it cannot be king because it was checked earlier if the king can save itself
    vector<Figure*> m_attackFigures;

    bool checkDiagonal(const int &, const int &, const pair<int,int> &);
    bool checkDiagonals(const int &, const int &);
    bool checkRankOrFile(const int &, const int &, const pair<int,int> &);
    bool checkRanksAndFiles(const int &, const int &);
    bool checkKnight(const int &, const int &, const pair<int,int> &);
    bool checkKnights(const int &, const int &);
};


#endif //CHECKATTACKSONFIELD_HPP
