#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

Mix_Music* loadMusic(const char* path);
void play(Mix_Music* music);

Mix_Chunk* loadSound(const char* path);
void play(Mix_Chunk* chunk);

#endif