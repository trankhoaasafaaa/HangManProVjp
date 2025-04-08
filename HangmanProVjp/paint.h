#ifndef paint_H
#define paint_H

#pragma once

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Paint
{
	int width, height;

	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color color;

public:
	Paint(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);

	SDL_Texture* loadTexture(std::string path);
	SDL_Texture* loadImage(std::string text, SDL_Rect* srcRest, SDL_Rect* desRect, float _x = 0, float _y = 0);
	SDL_Texture* textTexture(std::string text, SDL_Rect* srcRest, SDL_Rect* desRect, float _x = 0, float _y = 0);
	
	bool createImage(SDL_Texture* texture);

};
#endif // paint_H
