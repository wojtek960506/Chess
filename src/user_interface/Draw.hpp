#ifndef DRAW_HPP
#define DRAW_HPP

extern "C" {
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
}

class SDL_Exception2 {};

//to draw not filled rectangle ; last argument is used to distinguish how thick is rectangle

/**
 * function to draw rectangle on the board with the given thickness
 * @param renderer
 * @param width
 * @param height
 * @param beginX
 * @param beginY
 * @param colorR
 * @param colorG
 * @param colorB
 * @param thickness
 * @return object representing the drawn area
 */
SDL_Rect drawRect(	SDL_Renderer* renderer, int width, int height, int beginX, int beginY,
                      Uint8 colorR, Uint8 colorG, Uint8 colorB, int thickness = 1);

/**
 * function used to draw the filled rectangle
 * @param renderer
 * @param width
 * @param height
 * @param beginX
 * @param beginY
 * @param colorR
 * @param colorG
 * @param colorB
 * @return object representing the drawn area
 */
SDL_Rect drawFilledRect(SDL_Renderer* renderer, int width, int height, int beginX, int beginY,
                        Uint8 colorR, Uint8 colorG, Uint8 colorB);

/**
 * function used to draw text
 * @param renderer
 * @param width
 * @param height
 * @param text
 * @param fontName
 * @param fontSize
 * @param fR
 * @param fG
 * @param fB
 * @param bR
 * @param bG
 * @param bB
 * @return object representing the area of texture of text
 */
SDL_Rect drawText (SDL_Renderer* renderer, int width, int height, const char* text, const char* fontName,
				int fontSize, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB);

/**
 * function used to draw image from a file
 * @param renderer
 * @param width
 * @param height
 * @param beginX
 * @param beginY
 * @param image
 */
void drawImage ( SDL_Renderer* renderer, int width, int height, int beginX, int beginY, const char * image);

#endif //DRAW_HPP