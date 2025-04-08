#ifndef GOGAME_H
#define GOGAME_H

#include <string>
#include <cstring>

#include "graphics.h"

using namespace std;

class GoGame
{
	graphics* SDL;

	const int Max_fail_guess = 7;

	bool quit;
	
	char guessChar;

	string Topic;
	string TopicName;
	string guessedWord;
	string badGuess;
	string guessedStr;
	string secretWord;

	int badGuessCount;
	int maxSuggest;
	int usedSuggest;
	int win;
	int loss;
	int difficulty;
	int playTime;
	int timeLeft = 100;
	int animatedTime;
	
	time_t startTime;

public:
	GoGame(graphics*, int);
	
	Mix_Chunk* touchSound;
	Mix_Chunk* winSound;
	Mix_Chunk* loseSound;

	bool playing;
	bool guessing();

	void startGame();
	void chooseTopic();
	void chooseTopicEvent();
	void chooseDifficulty();
	void renderDifficulty();
	void chooseDifficultyEvent();
	void startScreenEvent();
	void renderStartScreen();
	void renderTopic();
	void guessEvent();
	void handleGuess();
	void getSuggest();
	void updateGuessedWord();
	void updateTime();
	void badGuessed();
	void renderGame();
	void gameOver();
	void renderGameOver(int index);
	void createGameOver();
	void renderBird(char, int);
	void birdEvent(SDL_Event&, bool&);
	void checkContinue();
};

#endif
