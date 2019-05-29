#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <vector>
#include <iostream>
#include "../main_logic/ConstantsAndEnums.hpp"
#include "../main_logic/Board.hpp"
#include "../main_logic/FieldToMove.hpp"

using namespace std;

class King;

/**
 * abstract class to decribe figure position, type and color
 * it provides the interface for the method to retrieve all fields where we can move with the figure in current state of game
 */
class Figure {
public: 
	Figure() {}
	Figure(FigureType figType, FigureColor figColor, const int & numPos, const int & letPos, const unsigned int & moves = 0)
	    : m_figType(figType), m_figColor(figColor), m_numPos(numPos), m_letPos(letPos), m_moves(moves) {}
	virtual ~Figure() { }

	virtual Figure * clone () const & = 0;

	int getNumPos() const { return m_numPos; }
	int getLetPos() const { return m_letPos; }
	int getFigType() const { return m_figType; }
	int getFigColor() const { return m_figColor; }
	unsigned int getMoves() const { return m_moves; }
	virtual void move(Board * board, const int & numPos, const int & letPos);
	virtual vector < FieldToMove > getFullRangeOfMoves(King * king, Board * board) = 0;

	bool checkCastlingAfterMovement( King * king, Board * board,
	                                const int & numPosBefore, const int & letPosBefore,
	                                const int & numPosAfter, const int & letPosAfter);

	//virtual string print() const;
	friend ostream & operator << (ostream &, const Figure &);


protected:
	FigureType m_figType;
	FigureColor m_figColor;
	int m_numPos;
	int m_letPos;
	unsigned int m_moves;
};

/**
 * class to represent figure KING - it provides movements of this figure
 */
class King : public Figure {
public:
    King (FigureColor figColor, const int & numPos, const int & letPos, const unsigned int & moves = 0)
            : Figure(FigureType::KING, figColor, numPos, letPos, moves) {}
    vector < FieldToMove > getFullRangeOfMoves(King * king, Board * board) override;

    virtual King * clone () const & override { return new King (*this); }
private:
    void getMove(King *, Board *, vector<FieldToMove> &, const int &, const int &);
    void checkCastling(Board *, vector<FieldToMove> &);
};

/**
 * class to represent figure PAWN - it provides movements of this figure
 * it has additional variable to decide about en passant movement
 */
class Pawn : public Figure {
public:
	Pawn (FigureColor figColor, const int & numPos, const int & letPos, const unsigned int & moves = 0, bool enPassantFlag = false)
	    : Figure(FigureType::PAWN, figColor, numPos, letPos, moves), m_enPassantFlag(enPassantFlag)  {}
	vector < FieldToMove > getFullRangeOfMoves(King * king, Board * board) override;
    virtual void move(Board * board, const int & numPos, const int & letPos);
	void disallowEnPassant() { m_enPassantFlag = false; }
    bool canBeCapturedWithEnPassant() const { return m_enPassantFlag; }

    virtual Pawn * clone () const & override { return new Pawn (*this); }
private:
    bool m_enPassantFlag;
    void getNormalMove(King *, Board *, vector<FieldToMove> &, const int &, const int &, const unsigned int &, FigureColor);
    void getCaptureMove(King *, Board *, vector<FieldToMove> &, const int &, const int &);
    void getEnPassantMove(King *, Board *, vector<FieldToMove> &, const int &, const int &, EnPassantSide);
    bool checkCastlingAfterMovementEnPassant (  King * king, Board * board,
                                                const int & numPosBefore, const int & letPosBefore,
                                                const int & numPosAfter, const int & letPosAfter);
};

/**
 * class to represent figure BISHOP - it provides movements of this figure
 */
class Bishop : public Figure {
public:
	Bishop (FigureColor figColor, const int & numPos, const int & letPos, const unsigned int & moves = 0)
	    : Figure(FigureType::BISHOP, figColor, numPos, letPos, moves) {}
	vector < FieldToMove > getFullRangeOfMoves(King * king, Board * board) override;

    virtual Bishop * clone () const & override { return new Bishop (*this); }
private:
    void getMove(King *, Board *, vector<FieldToMove> &, const int &, const int &);
};

/**
 * class to represent figure KNIGHT - it provides movements of this figure
 */
class Knight : public Figure {
public:
	Knight (FigureColor figColor, const int & numPos, const int & letPos, const unsigned int & moves = 0)
	    : Figure(FigureType::KNIGHT, figColor, numPos, letPos, moves) {}
	vector < FieldToMove > getFullRangeOfMoves(King * king, Board * board) override;

    virtual Knight * clone () const & override { return new Knight (*this); }
private:
    void getMove(King *, Board *, vector<FieldToMove> &, const int &, const int &);
};

/**
 * class to represent figure ROOK - it provides movements of this figure
 */
class Rook : public Figure {
public:
	Rook (FigureColor figColor, const int & numPos, const int & letPos, const unsigned int & moves = 0)
	    : Figure(FigureType::ROOK, figColor, numPos, letPos, moves) {}
	vector < FieldToMove > getFullRangeOfMoves(King * king, Board * board) override;

    virtual Rook * clone () const & override { return new Rook (*this); }
private:
    void getMove(King *, Board *, vector<FieldToMove> &, const int &, const int &);
};

/**
 * class to represent figure QUEEN - it provides movements of this figure
 */
class Queen : public Figure {
public:
	Queen (FigureColor figColor, const int & numPos, const int & letPos, const unsigned int & moves = 0)
	    : Figure(FigureType::QUEEN, figColor, numPos, letPos, moves) {}
	vector < FieldToMove > getFullRangeOfMoves(King * king, Board * board) override;

    virtual Queen * clone () const & override { return new Queen (*this); }
private:
    void getMove(King *, Board *, vector<FieldToMove> &, const int &, const int &);
};

#endif //FIGURE_HPP