#include "SDL_Button.hpp"

SDL_Button::SDL_Button() {
	m_position.x = 0;
	m_position.y = 0;
	m_width = 0;
	m_height = 0;
}

SDL_Button::SDL_Button (unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	m_position.x = x;
	m_position.y = y;
	m_width = width;
	m_height = height;
}

void SDL_Button::setPosition(unsigned int x, unsigned int y) {
	m_position.x = x;
	m_position.y = y;
}

void SDL_Button::setSize (unsigned int width, unsigned int height) {
	m_width = width;
	m_height = height;
}

bool SDL_Button::handleEvent(SDL_Event* e) {
	//if mouse event happened
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		//get mouse position
		int x,y;
		SDL_GetMouseState(&x, &y);
		//check if the mouse is inside button
		bool inside = true;
		if (x < m_position.x || x > (int)(m_position.x + m_width) || y < m_position.y || y > (int)(m_position.y + m_height) )
			inside = false;
		return inside;
	} else	return false;
}

