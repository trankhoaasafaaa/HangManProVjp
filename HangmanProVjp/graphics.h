#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "paint.h"

using namespace std;

class graphics
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	Paint* paint;

	string title;
	
	int width;
	int height;
	
public:
	
	graphics(string _title, int _width, int _height);
	~graphics();

	void log_Error(ostream& out, const string& error, bool check);
	void openFont(string s, int size);
	void createTextTexture(string s, int x, int y);
	void createImage(string s, int x, int y);
	void createBackGround(string s);
	void updateScreen();
};

#endif //GRAPHICS_H
