#include "AppWindow.hpp"

#include <iostream>
using namespace std;

void AppWindow::init() {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        throw SDL_Exception();
    } else {
        //Create window
        m_window = SDL_CreateWindow( "Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( m_window == NULL ) {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            throw SDL_Exception();
        } else {
            //Create renderer for window
            m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
            if( m_renderer == NULL ) {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                throw SDL_Exception();
            } else {
                SDL_SetRenderDrawColor( m_renderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderClear( m_renderer );
                //Initialize SDL_ttf
                if( TTF_Init() == -1 ) {
                    cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
                    throw SDL_Exception();
                }
            }
        }
    }
}

void AppWindow::close()
{
    //Destroy window
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_window );
    m_window = nullptr;
    m_renderer = nullptr;
    //Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

