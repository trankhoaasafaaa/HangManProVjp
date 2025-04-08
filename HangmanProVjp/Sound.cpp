#include "Sound.h"
#include <SDL.h>

Mix_Music* loadMusic(const char* path)
{
	Mix_Music* music = Mix_LoadMUS(path);
	if (!music)
	{
		SDL_Log("Failed to load music: %s", Mix_GetError());
	}
	return music;
}

void play(Mix_Music* music)
{
	if (!music) return;

	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(music, -1);
	else if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
}

Mix_Chunk* loadSound(const char* path)
{
	Mix_Chunk* chunk = Mix_LoadWAV(path);
	if (!chunk)
	{
		SDL_Log("Failed to load sound: %s", Mix_GetError());
	}
	return chunk;
}

void play(Mix_Chunk* chunk)
{	
	if (chunk)
		Mix_PlayChannel(-1, chunk, 0);
}