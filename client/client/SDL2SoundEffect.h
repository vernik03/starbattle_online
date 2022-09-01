#pragma once
#include <vector>
#include "SDL_mixer.h"
#include "SDL.h"

class SDL2SoundEffect
{
public:
	SDL2SoundEffect();
	~SDL2SoundEffect();

	void addSoundEffect(const char* path);
	void playSoundEffect(const int which);
	void playMusicEffect(const int which);
private:
	std::vector<Mix_Chunk*> mSoundEffectBank;
};

