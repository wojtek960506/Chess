#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include "ConstantsAndEnums.hpp"
#include "../user_interface/BaseView.hpp"
#include "../user_interface/MainMenuView.hpp"
#include "../user_interface/NewGameView.hpp"
#include "../user_interface/ChoosePlayersView.hpp"
#include "../user_interface/EndGameView.hpp"
#include "../user_interface/HelpView.hpp"
#include "Board.hpp"
#include "../figures/Figure.hpp"
#include "../user_interface/AppWindow.hpp"
#include "Game.hpp"
#include <queue>
#include <typeinfo>

#include "../user_interface/PromotionView.hpp"
#include "../user_interface/LoadGameView.hpp"

using namespace std;

/**
 * class representing the main controller of the application ; it manages which view to be shown
 */
class MainController {
public:
    MainController();
    ~MainController();
    void run();
private:
    AppWindow * m_appWindow;
    queue<BaseView*> m_views;
    Game * m_game;

};

#endif //MAINCONTROLLER_HPP
