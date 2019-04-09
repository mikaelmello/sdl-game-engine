#define SDL_INCLUDE_MIXER
#define SDL_INCLUDE_IMAGE
#define SDL_INCLUDE_TTF
#include "SDL_include.h"
#include "Resources.hpp"
#include "Helpers.hpp"
#include "Game.hpp"
#include <string>
#include <utility>
#include <algorithm>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(const std::string& file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        throw std::runtime_error("Could not load texture from file " + file + ": " + IMG_GetError());
    }

    std::shared_ptr<SDL_Texture> textureSp(texture, [=](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    imageTable.insert(std::make_pair(file, textureSp));
    return textureSp;
}

std::shared_ptr<Mix_Music> Resources::GetMusic(const std::string& file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        throw std::runtime_error("Could not load music from file " + file + ": " + Mix_GetError());
    }

    std::shared_ptr<Mix_Music> musicSp(music, [=](Mix_Music* music) { Mix_FreeMusic(music); });
    musicTable.insert(std::make_pair(file, musicSp));
    return musicSp;
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(const std::string& file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr) {
        throw std::runtime_error("Could not load sound from file " + file + ": " + Mix_GetError());
    }

    std::shared_ptr<Mix_Chunk> chunkSp(chunk, [=](Mix_Chunk* chunk) { Mix_FreeChunk(chunk); });
    soundTable.insert(std::make_pair(file, chunkSp));
    return chunkSp;
}

std::shared_ptr<TTF_Font> Resources::GetFont(const std::string& file, int fontSize) {
    auto key = file + std::to_string(fontSize);
    auto it = fontTable.find(key);
    if (it != fontTable.end()) {
        return it->second;
    }

    TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
    if (font == nullptr) {
        throw std::runtime_error("Could not load font from file " + file + ": " + TTF_GetError());
    }

    std::shared_ptr<TTF_Font> fontSp(font, [=](TTF_Font* font) { TTF_CloseFont(font); });
    fontTable.insert(std::make_pair(key, fontSp));
    return fontSp;
}

void Resources::ClearImages() {
    for(auto it = imageTable.begin(); it != imageTable.end();) {
        auto sp = it->second;
        if (sp.unique()) {
            it = imageTable.erase(it);
        } else {
            it++;
        }
    }
}

void Resources::ClearMusics() {
    for(auto it = musicTable.begin(); it != musicTable.end();) {
        auto sp = it->second;
        if (sp.unique()) {
            it = musicTable.erase(it);
        } else {
            it++;
        }
    }
}

void Resources::ClearSounds() {
    for(auto it = soundTable.begin(); it != soundTable.end();) {
        auto sp = it->second;
        if (sp.unique()) {
            it = soundTable.erase(it);
        } else {
            it++;
        }
    }
}
