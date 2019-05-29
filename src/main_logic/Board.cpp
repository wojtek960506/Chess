#include <iostream>

#include "Board.hpp"

using namespace std;

/**
 * default constructor of class Board
 */
Board::Board() {
    for (unsigned int i = 0 ; i < BOARD_SIZE ; ++i) {
        vector <Figure*> tmp;
        for (unsigned int j = 0 ; j < BOARD_SIZE ; ++j) {
            tmp.push_back(nullptr);
        }
        m_boardArray.push_back(tmp);
    }
}

/**
 * copy constuctor of class board
 * @param board
 */
Board::Board(const Board & board) {
    for (unsigned int i = 0 ; i < BOARD_SIZE ; ++i) {
        vector <Figure*> tmp;
        for (unsigned int j = 0 ; j < BOARD_SIZE ; ++j) {
            tmp.push_back(board.m_boardArray[i][j]);
        }
        m_boardArray.push_back(tmp);
    }
}

/**
 * operator of assignment for class board
 * @param board
 * @return
 */
Board & Board::operator = (const Board & board) {
    if (this == &board) return *this;
    for (auto & a : m_boardArray) for (auto & p : a) p = nullptr;
    for (unsigned int i = 0 ; i < BOARD_SIZE ; ++i) {
        vector <Figure*> tmp;
        for (unsigned int j = 0 ; j < BOARD_SIZE ; ++j) {
            tmp.push_back(board.m_boardArray[i][j]);
        }
        m_boardArray.push_back(tmp);
    }
    return *this;
}

/**
 * destructor for class board ; it just sets all pointers of objects to nullptr
 */
Board::~Board() {
	for (auto & a : m_boardArray) for (auto & p : a) p = nullptr;
}

/**
 * function to get pointer to figure which "stands" on the given position
 * @param rank - numerical position (row)
 * @param file - letter position (column)
 * @return
 */
Figure * Board::getFigureAtPos(const int & rank, const int & file) {
    if (rank < 0 || rank > (int)(BOARD_SIZE-1) || file < 0 || file > (int)(BOARD_SIZE-1)) throw InvalidPosition();
    return m_boardArray[rank][file];
}

/**
 * function sets pointer to Figure on the given field to nullptr
 * @param rank - numerical position (row)
 * @param file - letter position (column)
 */
void Board::resetPtrAtPos(const int & rank, const int & file) {
    if (rank < 0 || rank > (int)(BOARD_SIZE-1) || file < 0 || file > (int)(BOARD_SIZE-1)) throw InvalidPosition();
    m_boardArray[rank][file] = nullptr;
}