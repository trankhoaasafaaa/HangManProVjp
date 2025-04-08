#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "graphics.h"

using namespace std;

graphics::graphics(string _title, int _width, int _height)
	: title(_title), width(_width), height(_height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		log_Error(cout, "SDL_Init_Error", true);
	if (TTF_Init() < 0)
		log_Error(cout, "TTF_Init_Error", true);
	
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window==nullptr)
		log_Error(cout, "Window_Error", true);
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		log_Error(cout, "Audio_Error", true);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer==nullptr)
		log_Error(cout, "Renderer_Error", true);
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, width, height);
}

graphics::~graphics()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
}

void graphics::log_Error(ostream& out, const string& error, bool check)
{
	out << error << SDL_GetError() << std::endl;
	if (check)
	{
		SDL_Quit();
		exit(1);
	}
}

void graphics::openFont(string s, int size)
{
	font = TTF_OpenFont(s.c_str(), size);
	paint = new Paint(window, renderer, font);
}

void graphics::createTextTexture(string s, int x, int y)
{
	SDL_Rect srcRest;
	SDL_Rect desRect;
	SDL_Texture* texture = NULL;
	texture = paint->textTexture(s, &srcRest, &desRect, x, y);
	SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
	SDL_DestroyTexture(texture);
}

void graphics::createImage(string s, int x, int y)
{
	SDL_Rect srcRest;
	SDL_Rect desRect;
	SDL_Texture* texture = NULL;
	texture = paint->loadImage("img\\" + s, &srcRest, &desRect, x, y);
	SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
	SDL_DestroyTexture(texture);
}

void graphics::createBackGround(string s)
{
	SDL_Texture* texture = NULL;
	texture = paint->loadTexture("img\\" + s);	
	paint->createImage(texture);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
}

void graphics::updateScreen()
{
	SDL_RenderPresent(renderer);
}