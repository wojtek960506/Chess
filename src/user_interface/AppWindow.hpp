#ifndef APPWINDOW_HPP
#define APPWINDOW_HPP

extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}

#include "../main_logic/ConstantsAndEnums.hpp"

/**
 * class to throw exception related to SDL
 */
class SDL_Exception{};

/**
 * class to represent the main window of the application and its initialization
 */
class AppWindow {
public:
    AppWindow() { init(); }
    ~AppWindow() { close(); }
    SDL_Renderer * getRenderer() const { return m_renderer; }
private:
    void init();
    void close();
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
};


#endif //APPWINDOW_HPP
