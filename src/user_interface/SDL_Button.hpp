#ifndef SDL_BUTTON_HPP
#define SDL_BUTTON_HPP

extern "C" {
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
}

/**
 * class to catch the mouse click
 */
class SDL_Button {
public:
	SDL_Button(); //initializes internal variables
	SDL_Button(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	void setPosition (unsigned int x, unsigned int y); //sets top left position
	void setSize (unsigned int width, unsigned int height); //sets size
	bool handleEvent (SDL_Event* e); //handles mouse event
	void render(); //shows button sprite
private:
	SDL_Point m_position; //top left position
	unsigned int m_width;
	unsigned int m_height;
};

#endif //SDL_BUTTON_HPP