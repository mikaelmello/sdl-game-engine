

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Sound.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Resources.hpp"
#include "Component.hpp"
#include <stdexcept>
#include <string>

Sound::Sound(GameObject& associated) : Component(associated), channel(-1) {}

Sound::Sound(GameObject& associated, const std::string& file) : Sound(associated) {
    Open(file);
}

Sound::~Sound() {}

void Sound::Open(const std::string& file) {
    chunk = Resources::GetSound(file);
}

void Sound::Play(int times) {
    int availableChannel = Mix_PlayChannel(-1, chunk.get(), times - 1);
    if (availableChannel == -1) {
        throw std::runtime_error("Could not play sound: " + std::string(Mix_GetError()));
    }
    Mix_Volume(availableChannel, MIX_MAX_VOLUME);
    channel = availableChannel;
}

void Sound::Stop() {
    if (chunk && channel != -1) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Render() {}

void Sound::Update(float dt) {}

bool Sound::Is(const std::string& type) const {
    return type == std::string("Sound");
}

bool Sound::IsOpen() const {
    return (bool)chunk;
}

