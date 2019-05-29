#include "MainController.hpp"

/**
 * default constructor of the class MainController
 */
MainController::MainController() {
    m_appWindow = new AppWindow();
    m_game = nullptr;
}

/**
 * destructor of the class MainController
 */
MainController::~MainController() {
    delete m_appWindow;
    if (m_game != nullptr) delete m_game;
}

/**
 * main function to run the game and manage which view to be shown
 */
void MainController::run() {
    m_views.push(new MainMenuView(m_appWindow->getRenderer()));
    PlayerType player1 = PlayerType::NORMAL_PLAYER;
    PlayerType player2 = PlayerType::NORMAL_PLAYER;
    GameResult gameResult = GameResult::DRAW_RESULT;

    while(!m_views.empty()) {
        BaseView * currentView = m_views.front(); //get first view
        m_views.pop(); //remove this view
        WhichViewNext nextView = currentView->run();

        //at this point we will be after exiting the view of the game
        if (m_game != nullptr) {
            gameResult = m_game->m_gameResult;
        }

        //update information of players if we have just proceeded the view to choose the type
        if (typeid(*currentView) == typeid(ChoosePlayersView)) {
            player1 = dynamic_cast<ChoosePlayersView *>(currentView)->m_playerWhite;
            player2 = dynamic_cast<ChoosePlayersView *>(currentView)->m_playerBlack;
        }

        delete currentView; //current view finished execution so I will delete it
        switch (nextView) {
            case WhichViewNext::CHOOSE_PLAYER:
                m_views.push(new ChoosePlayersView(m_appWindow->getRenderer()));
                break;
            case WhichViewNext::NEW_GAME:
                if (m_game != nullptr)
                    delete m_game;
                m_game = new Game(player1, player2);
                m_views.push(new NewGameView(m_appWindow->getRenderer(), m_game));
                break;
            case WhichViewNext ::LOAD_GAME:
                m_views.push(new LoadGameView(m_appWindow->getRenderer(), m_game));
                break;
            case WhichViewNext::START_GAME_FROM_STATE:
                m_views.push(new NewGameView(m_appWindow->getRenderer(), m_game));
                break;
            case WhichViewNext::END_GAME:
                m_views.push(new EndGameView(m_appWindow->getRenderer(), gameResult));
                break;
            case WhichViewNext::HELP:
                m_views.push(new HelpView(m_appWindow->getRenderer()));
                break;
            case WhichViewNext::EXIT: //just leave the program
                break;
            case WhichViewNext::MAIN_MENU:
                m_views.push(new MainMenuView(m_appWindow->getRenderer()));
                break;
            default: //in case of some view which is not defined close app
                break;
        }
    }
}

