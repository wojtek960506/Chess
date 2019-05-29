#include "Draw.hpp"

#include <iostream>
using namespace std;

//to draw not filled rectangle ; last argument is used to distinguish how thick is rectangle
SDL_Rect drawRect(	SDL_Renderer* renderer, int width, int height, int beginX, int beginY,
				Uint8 colorR, Uint8 colorG, Uint8 colorB, int thickness) {
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, 0x00);
	for (int i = 0 ; i < thickness ; ++i) {
		rect = { beginX+i, beginY+i, width-2*i, height-2*i };
		SDL_RenderDrawRect (renderer, &rect);
	}
	return rect;
}

SDL_Rect drawFilledRect(SDL_Renderer* renderer, int width, int height, int beginX, int beginY,
                        Uint8 colorR, Uint8 colorG, Uint8 colorB) {
	SDL_Rect rect;
	rect = {beginX, beginY, width, height};
	SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, 0x00);
	SDL_RenderFillRect( renderer, &rect);
	return rect;
}

SDL_Rect drawText ( SDL_Renderer* renderer, int middle_x, int middle_y, const char* text, const char* fontName, int fontSize,
                Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB)
{
	TTF_Font* font = TTF_OpenFont(fontName, fontSize);
	if (font == NULL) throw SDL_Exception2();

	SDL_Color foregroundColor = { fR, fG, fB, 255 };
	SDL_Color backgroundColor = { bR, bG, bB, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Shaded (font, text, foregroundColor, backgroundColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

	int text_w = textSurface->w;
    int text_h = textSurface->h;

	SDL_Rect textLocation = {middle_x - text_w/2, middle_y - text_h/2, text_w, text_h};

	SDL_RenderCopy(renderer, textTexture, nullptr, &textLocation);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

	return textLocation;
}

void drawImage ( SDL_Renderer* renderer, int width, int height, int beginX, int beginY, const char * image) {
    SDL_Rect rect = {beginX, beginY, width, height};
    SDL_Surface * surface = IMG_Load(image);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}