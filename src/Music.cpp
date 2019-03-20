#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Music.hpp"
#include "Resources.hpp"
#include <string>
#include <stdexcept>

Music::Music() : music(nullptr) {}

Music::Music(const std::string& file) : Music() {
    Open(file);
}

void Music::Open(const std::string& file) {
    music = Resources::GetMusic(file);
}

void Music::Play(int times) {
    if (music == nullptr) {
        throw std::invalid_argument("Can not play music, file not open");
        return;
    }

    int return_code = Mix_PlayMusic(music, times);
    if (return_code != 0) {
        throw std::runtime_error("Could not play music: " + std::string(Mix_GetError()));
    }
}

void Music::Stop(int msTostop) {
    int return_code = Mix_FadeOutMusic(msTostop);
    if (return_code != 0) {
        throw std::runtime_error("Could not stop music: " + std::string(Mix_GetError()));
    }
}

bool Music::IsOpen() const {
    return music != nullptr;
}

Music::~Music() {}
