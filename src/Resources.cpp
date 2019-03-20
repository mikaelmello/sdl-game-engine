#define SDL_INCLUDE_MIXER
#include "SDL_include.h"
#include "Resources.hpp"
#include <string>
#include <algorithm>

std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

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

void Resources::ClearSounds() {
    std::for_each(
        soundTable.begin(),
        soundTable.end(),
        [](std::unordered_map<std::string, Mix_Chunk*>::value_type item) { Mix_FreeChunk(item.second); }
    );
}
