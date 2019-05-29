#ifndef READSTATE_HPP
#define READSTATE_HPP

#include <fstream>

#include "../main_logic/Game.hpp"

using namespace std;

/**
 * class to read the state from the file
 */
class ReadState {
public:
    ReadState() {}
    ~ReadState() { }
    ReadState(string filename) : m_filename(filename) {}
    bool readStateFromFile();
    Game * getGamePtr() const { return m_game; }
private:
    string m_filename;
    Game * m_game = nullptr;

    bool readFigure(const string & figure, set<Figure*> & figures);
    bool readFieldToCheck(const string & checkField, vector<pair<int,int>> & checkFields);
};

#endif //READSTATE_HPP
