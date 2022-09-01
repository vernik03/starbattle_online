#include "SDL2SoundEffect.h"
#include <iostream>
#include <chrono>
#include <thread>


SDL2SoundEffect::SDL2SoundEffect()
{
	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "cannot init", Mix_GetError());
		exit(-1);
	}
}

SDL2SoundEffect::~SDL2SoundEffect()
{
	SDL_Quit();
}

void SDL2SoundEffect::addSoundEffect(const char* path)
{
	Mix_Chunk* tmp_chunk = Mix_LoadWAV(path);

	if (tmp_chunk != nullptr) {
		mSoundEffectBank.push_back(tmp_chunk);
		////std::cout << (mSoundEffectBank.size() - 1) << " Sound ready, path " << path << "\n";
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot init sound %s", Mix_GetError());
	}
}

void SDL2SoundEffect::playSoundEffect(const int which)
{
	if (which > mSoundEffectBank.size() - 1) {
		////std::cout << "Sound out of range\n";
	}
	else {

		int ans = Mix_PlayChannel(0, mSoundEffectBank[which], 0);
		if (ans != 0) {
			////std::cout << "Sound error!\n";

		}
		else {
			//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			////std::cout << "Sound over\n";
		}
	}

}

void SDL2SoundEffect::playMusicEffect(const int which)
{
	if (which > mSoundEffectBank.size() - 1) {
		//std::cout << "Sound out of range\n";
	}
	else {

		int ans = Mix_PlayChannel(1, mSoundEffectBank[which], -1);
		if (ans != 0) {
			//std::cout << "Sound error!\n";

		}
		else {
			//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			//std::cout << "Sound over\n";
		}
	}

}
