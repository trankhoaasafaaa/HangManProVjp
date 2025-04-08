#include <iostream>
#include <ctime>

#include "GoGame.h"
#include "graphics.h"
#include "Sound.h"
#include "defs.h"

using namespace std;

int main(int argc, char* argv[])
{
	graphics* SDL = new graphics(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL->openFont("KOPIKOO.ttf", 33);
	GoGame* game = new GoGame(SDL, Play_Time);
	game->touchSound = loadSound("sound/touch.wav");
	game->renderStartScreen();
	game->startScreenEvent();
	while (game->playing)
	{
		game->startGame();
		while (game->guessing())
		{
			game->renderGame();
			game->guessEvent();
			game->handleGuess();
			game->updateTime();
		}
		game->gameOver();
	}
	return 0;
}