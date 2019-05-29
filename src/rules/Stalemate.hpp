#ifndef STALEMATE_HPP
#define STALEMATE_HPP

#include "Rule.hpp"
#include "../main_logic/Game.hpp"

/**
 * class to represent the rule of stalemate - current player's king is not checked and the player don't have any possibility to move
 */
class Stalemate : public Rule {
public:
    Stalemate(Board * board, Game * game) : Rule(board), m_game(game) {}
    bool check() override;
private:
    Game * m_game;
};

#endif //STALEMATE_HPP
