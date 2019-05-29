#ifndef SAVESTATE_HPP
#define SAVESTATE_HPP

#include "Game.hpp"
#include <fstream>

/**
 * class used to save current state of the game to the file
 */
class SaveState {
public:
    SaveState (string filename) : m_filename(filename) {}
    bool saveStateToFile(Game * game);
private:
    bool saveFigures(fstream & file, Game * game);
    bool saveFigure (fstream & file, const Figure * figure);
    string m_filename;

};

#endif //SAVESTATE_HPP
