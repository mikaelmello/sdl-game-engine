#define SDL_INCLUDE_MIXER
#include "SDL_include.h"
#include "Resources.hpp"
#include "Game.hpp"
#include <string>
#include <algorithm>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(const std::string& file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (texture == nullptr) {
        throw std::runtime_error("Could not load texture from file " + file + ": " + IMG_GetError());
    }

    imageTable.insert(std::make_pair(file, texture));
    return texture;
}

Mix_Music* Resources::GetMusic(const std::string& file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        throw std::runtime_error("Could not load music from file " + file + ": " + Mix_GetError());
    }

    musicTable.insert(std::make_pair(file, music));
    return music;
}

Mix_Chunk* Resources::GetSound(const std::string& file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());

    if (chunk == nullptr) {
        throw std::runtime_error("Could not load sound from file " + file + ": " + Mix_GetError());
    }

    soundTable.insert(std::make_pair(file, chunk));
    return chunk;
}

void Resources::ClearImages() {
    std::for_each(
        imageTable.begin(),
        imageTable.end(),
        [](std::unordered_map<std::string, SDL_Texture*>::value_type item) { SDL_DestroyTexture(item.second); }
    );

    imageTable.clear();
}

void Resources::ClearMusics() {
    std::for_each(
        musicTable.begin(),
        musicTable.end(),
        [](std::unordered_map<std::string, Mix_Music*>::value_type item) { Mix_FreeMusic(item.second); }
    );

    musicTable.clear();
}

void Resources::ClearSounds() {
    std::for_each(
        soundTable.begin(),
        soundTable.end(),
        [](std::unordered_map<std::string, Mix_Chunk*>::value_type item) { Mix_FreeChunk(item.second); }
    );

    soundTable.clear();
}
