

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Sound.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include <stdexcept>
#include <string>

Sound::Sound(GameObject& associated) : Component(associated), chunk(nullptr) {}

Sound::Sound(GameObject& associated, const std::string& file) : Sound(associated) {
    Open(file);
}

Sound::~Sound() {
    Stop();
    if (chunk != nullptr) {
        Mix_FreeChunk(chunk);
    }
}

void Sound::Open(const std::string& file) {
    chunk = Mix_LoadWAV(file.c_str());

    if (chunk == nullptr) {
        throw std::runtime_error("Could not load sound from file " + file + ": " + Mix_GetError());
    }
}

void Sound::Play(int times) {
    int availableChannel = Mix_PlayChannel(-1, chunk, times - 1);
    if (availableChannel == -1) {
        throw std::runtime_error("Could not play sound: " + std::string(Mix_GetError()));
    }
    channel = availableChannel;
}

void Sound::Stop() {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Update(float dt) {}

bool Sound::Is(const std::string& type) {
    return type == std::string("Sound");
}

bool Sound::IsOpen() const {
    return chunk != nullptr;
}

