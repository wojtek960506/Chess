#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <set>
#include "ConstantsAndEnums.hpp"
//#include "Figure.hpp"

class Figure;

using namespace std;

/**
 * class to represent the chess board; it keeps pointers to figures, but not allocate its memory
 */
class Board {
public:
	Board();
	Board(const Board & board);
	Board & operator = (const Board & board);
	~Board(); //clear board

    void putFigure(Figure * figure, const unsigned int & rank, const unsigned int & file) { m_boardArray[rank][file] = figure; }
    vector<vector<Figure*>> getBoardArray() const { return m_boardArray; }
    Figure * getFigureAtPos(const int & rank, const int & file); //rank - row ; file - column
    void resetPtrAtPos(const int & rank, const int & file);
private:
	vector< vector<Figure*> > m_boardArray ;
};

#endif //BOARD_HPP