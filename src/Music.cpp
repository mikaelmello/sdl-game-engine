#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Music.hpp"
#include <string>

Music::Music() : music(nullptr) {}

Music::Music(std::string file) : music(nullptr) {
    Open(file);
}

void Music::Open(std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        throw "Failed to load music";
    }
}

void Music::Play(int times) {
    if (music == nullptr) {
        return;
    }

    int return_code = Mix_PlayMusic(music, times);
    if (return_code != 0) {
        throw "Failed to play music";
    }
}

void Music::Stop(int msTostop) {
    int return_code = Mix_FadeOutMusic(msTostop);
    if (return_code != 0) {
        throw "Failed to stop music";
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    Mix_FreeMusic(music);
}
