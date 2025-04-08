#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <ctime>
#include <cmath>

#include "GoGame.h"
#include "graphics.h"
#include "util.h"
#include "Sound.h"

using namespace std;

GoGame::GoGame(graphics* graphics, int time) : SDL(graphics), playTime(time)
{
    playing = true;
    win = 0;
    loss = 0;
}

void GoGame::startGame()
{
    quit = false;
    winSound = loadSound("sound/win.wav");
    loseSound = loadSound("sound/loss.wav");
    chooseTopic();
    chooseDifficulty();
    secretWord = chooseWord(Topic, difficulty);
    guessedWord = string(secretWord.length(), '-');
    for (int i = 0;i < secretWord.length();i++)
        if (secretWord[i] == ' ')
            guessedWord[i] = ' ';
    time(&startTime);
    animatedTime = 0;
    maxSuggest = 2;
    usedSuggest = 0;
    badGuessCount = 0;
    guessChar = ' ';
    badGuess = "";
    guessedStr = "";
}
void GoGame::renderStartScreen()
{
    SDL->createBackGround("backGround.png");
	SDL->openFont("KOPIKOO.ttf", 80);
    SDL->createTextTexture("HANGMAN", 270, 300);
	SDL->openFont("KOPIKOO.ttf", 20);
    SDL->createTextTexture("PRESS ENTER TO START", 315 , 400);
    SDL->updateScreen();
}
void GoGame::startScreenEvent()
{
    bool waiting = true;
    SDL_Event e;

    while (waiting && playing) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                playing = false;
                quit = true;
                waiting = false;
            }
            else if (e.type == SDL_KEYUP) 
            {
                play(touchSound);
                if (e.key.keysym.sym == SDLK_RETURN ||
                    e.key.keysym.sym == SDLK_RETURN2 ||
                    e.key.keysym.sym == SDLK_KP_ENTER) 
                    waiting = false;
                else if (e.key.keysym.sym == SDLK_ESCAPE) 
                {
                    playing = false;
                    quit = true;
                    waiting = false;
                }
            }
        }
    }
}

void GoGame::chooseTopic()
{
    Topic = "";
    while (Topic == "" && playing && !quit)
    {
        renderTopic();
        chooseTopicEvent();
    }
}

void GoGame::chooseTopicEvent()
{
    bool waiting = true;
    SDL_Event e;
    while (waiting && playing)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                playing = false;
                quit = true;
                waiting = false;
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    playing = false;
                    waiting = false;
                }
                else
                {
                    string KeyName = SDL_GetKeyName(e.key.keysym.sym);
                    if (KeyName.size() == 1 && KeyName[0] >= '1' && KeyName[0] <= '4')
                    {
                        play(touchSound);
                        switch (KeyName[0])
                        {
                        case '1':
                            Topic = "fruits.txt";
                            TopicName = "Fruits";
                            break;
                        case '2':
                            Topic = "animals.txt";
                            TopicName = "Animals";
                            break;
                        case '3':
                            Topic = "countries.txt";
                            TopicName = "Countries";
                            break;
                        case '4':
                            Topic = "sports.txt";
                            TopicName = "Sports";
                            break;
                        }
                        waiting = false;
                    }
                }
            }
        }
    }
}

void GoGame::renderTopic()
{
    SDL->createBackGround("backGround.png");
    SDL->createTextTexture("Choose word Topic:", 101, 50);
    SDL->createTextTexture("1. Fruits", 151, 100);
    SDL->createTextTexture("2. Animals", 151, 150);
    SDL->createTextTexture("3. Countries", 151, 200);
    SDL->createTextTexture("4. Sports", 151, 250);
    SDL->updateScreen();
}
void GoGame::chooseDifficulty() 
{
    difficulty = 0;
    while (difficulty == 0 && playing && !quit)
    {
        renderDifficulty();
        chooseDifficultyEvent();
    }
}
void GoGame::chooseDifficultyEvent()
{
    bool waiting = true;
    SDL_Event e;
    while(waiting && playing)
    {
        if (SDL_WaitEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                playing = false;
                quit = true;
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    playing = false;
                    waiting = false;
                }
                else
                {
                    string keyName = SDL_GetKeyName(e.key.keysym.sym);
                    if (keyName.size() == 1 && keyName[0] >= '1' && keyName[0] <= '3')
                    {
                        play(touchSound);
                        switch (keyName[0])
                        {
                        case '1':
                            difficulty = 1;
                            break;
                        case '2':
                            difficulty = 2;
                            break;
                        case '3':
                            difficulty = 3;
                            break;
                        }
                        waiting = false;
                    }
                }
            }
        }
    }
}

void GoGame::renderDifficulty() 
{
    SDL->createBackGround("backGround.png");
    SDL->createTextTexture("Topic: " + TopicName, 100, 50);
    SDL->createTextTexture("Choose word difficulty:", 100, 100);
    SDL->createTextTexture("1. Easy", 150, 150);
    SDL->createTextTexture("2. Hard", 150, 200);
    SDL->createTextTexture("3. RandomDifficulty", 150, 250);
    SDL->updateScreen();
}

void GoGame::renderBird(char guessedChar, int num) 
{
    time_t startT, endT;
    time(&startT);
    int i = -200;
    bool skip = false;
    SDL_Event e;
    string text = "Have " + to_string(num) + " '" + guessedChar + "'";
    while (i < 999 && !skip && playing && !quit) 
    {
        birdEvent(e, skip);
        int y = 40 + static_cast<int>(20 * sin(i / 30.0));
        SDL->createBackGround("backGround.png");
        SDL->createImage("bird.png", i, y);
        SDL->createTextTexture(text, i + 420, y + 225);
        SDL->createTextTexture("Press 'Space' to skip", 400, 850);
        SDL->updateScreen();
        i += 2;
    }
    time(&endT);
    animatedTime += difftime(endT, startT);
}

void GoGame::birdEvent(SDL_Event &e, bool& skip)
{
    if (SDL_PollEvent(&e)) 
    {
        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)
            skip = true;
        if (e.type == SDL_QUIT) 
        {
            playing = false;
            quit = true;
            skip = true;
        }
    }
}

void GoGame::guessEvent()
{
    SDL_Event e;
    guessChar = ' ';
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            playing = false;
            quit = true;
        }
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
            playing = false;
        else if (e.type == SDL_KEYUP)
        {
            play(touchSound);
            string KeyName = SDL_GetKeyName(e.key.keysym.sym);
            if (KeyName == "Escape")
                playing = false;
            else if (KeyName == "Space")
                guessChar = '?';
            else if (KeyName.size() == 1 && KeyName[0] >= 'A' && KeyName[0] <= 'Z')
                guessChar = KeyName[0];
        }
    }
}

void GoGame::handleGuess()
{
    if (guessChar == ' ')
        return;
    if (guessChar == '?')
        getSuggest();
    else if (contains(guessedWord, guessChar))
        return;
    else if (contains(secretWord, guessChar))
        updateGuessedWord();
    else if (!contains(badGuess, guessChar))
    {
        badGuessed();
        renderBird(guessChar, 0);
    }
}

void GoGame::updateGuessedWord()
{
    int len = guessedWord.length(), countChar = 0;
    for (int i = 0;i < len;i++)
    {
        if (secretWord[i] == guessChar)
        {
            guessedWord[i] = guessChar;
            countChar++;
        }
    }
    guessedStr += guessChar;
    renderBird(guessChar, countChar);
}

void GoGame::getSuggest()
{
    if (usedSuggest < maxSuggest)
    {
        usedSuggest++;
        while (true)
        {
            int i = rand() % guessedWord.size();
            if (guessedWord[i] == '-')
            {
                guessedWord[i] = secretWord[i];
				guessChar = secretWord[i];
                updateGuessedWord();
                break;
            }
        }
    }
}

void GoGame::badGuessed()
{
    badGuessCount++;
    badGuess += guessChar;
    guessedStr += guessChar;
}

bool GoGame::guessing()
{
    return playing && badGuessCount < Max_fail_guess && guessedWord != secretWord && timeLeft > 0;
}

void GoGame::renderGame()
{
    SDL->createBackGround("fail" + to_string(badGuessCount) + ".png");
    SDL->createTextTexture("Time: " + to_string(timeLeft), 750, 5);
    SDL->createTextTexture("Win: " + to_string(win), 750, 44);
    SDL->createTextTexture("Loss: " + to_string(loss), 750, 88);
    SDL->createTextTexture("Current guess: " + guessedWord, 100, 640);
    SDL->createTextTexture("Bad guesses: " + badGuess, 100, 690);
    SDL->createTextTexture("Used suggestions: " + to_string(usedSuggest) + "/" + to_string(maxSuggest), 100, 740);
    SDL->createTextTexture("Press SPACE to get suggest", 100, 790);
    SDL->createTextTexture("Press ESC to exit", 100, 820);
    SDL->updateScreen();
    SDL_Delay(16);
}

void GoGame::gameOver()
{
    if (guessedWord == secretWord)
    {
        win++;
        play(winSound);
    }
    else
    {
        loss++;
        play(loseSound);
    }
    createGameOver();
}
void GoGame::renderGameOver(int index)
{
    string result = (guessedWord == secretWord ? "win" : "loss");
    SDL->createBackGround(result + to_string(index) + ".png");
    if (timeLeft <= 0)
        SDL->createTextTexture("Time Up!!!!!", 750, 5);
    if (guessedWord == secretWord)
        SDL->createTextTexture("You win!", 100, 650);
    else
        SDL->createTextTexture("You lose!", 100, 700);
    SDL->createTextTexture("The Secret Word is : " + secretWord, 100, 750);
    SDL->createTextTexture("Press 'ESC' to exit, 'Enter' to play again!", 100, 800);
    SDL->updateScreen();
}

void GoGame::updateTime() 
{
    time_t now;
    time(&now);
    timeLeft = playTime - difftime(now, startTime) + animatedTime;
}

void GoGame::createGameOver()
{
    int imageIndex = 0;
    while (!quit) 
    {
        checkContinue();
        renderGameOver(imageIndex);
        SDL_Delay(210);
        imageIndex = (imageIndex + 1) % 4;
    }
}
void GoGame::checkContinue()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            playing = false;
            quit = true;
        }
        else if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                playing = false;
                quit = true;
            }
            else if (e.key.keysym.sym == SDLK_RETURN ||
                e.key.keysym.sym == SDLK_RETURN2 ||
                e.key.keysym.sym == SDLK_KP_ENTER)
            {
                playing = true;
                quit = true;
            }
        }
    }
}
