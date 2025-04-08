#include <iostream>
#include <cmath>
#include <cstdlib>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "paint.h"

using namespace std;

Paint::Paint(SDL_Window* window = nullptr, SDL_Renderer* _renderer = nullptr, TTF_Font* _font=nullptr)
	: renderer(_renderer), font(_font)
{
	if (window == nullptr) return;
	SDL_RenderGetLogicalSize(renderer, &width, &height);
	if (width == 0 || height == 0)
		SDL_GetWindowSize(window, &width, &height);
}

SDL_Texture* Paint::loadTexture(string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
			cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

SDL_Texture* Paint::loadImage(string path, SDL_Rect* srcRest, SDL_Rect* desRect, float _x, float _y)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
			cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
		SDL_FreeSurface(loadedSurface);
	}

	SDL_QueryTexture(newTexture, NULL, NULL, &srcRest->w, &srcRest->h);
	srcRest->x = 0;
	srcRest->y = 0;
	desRect->x = _x;
	desRect->y = _y;
	desRect->w = srcRest->w;
	desRect->h = srcRest->h;
	return newTexture;
}

SDL_Texture* Paint::textTexture(string text, SDL_Rect* srcRest, SDL_Rect* desRect, float _x, float _y) 
{
	SDL_Color fg = { 0, 0, 0 };
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), fg);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	TTF_SizeText(font, text.c_str(), &srcRest->w, &srcRest->h);
	srcRest->x = 0;
	srcRest->y = 0;
	desRect->x = _x;
	desRect->y = _y;
	desRect->w = srcRest->w;
	desRect->h = srcRest->h;
	return texture;
}

bool Paint::createImage(SDL_Texture* texture) 
{
	if (texture == NULL) return false;
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	return true;
}