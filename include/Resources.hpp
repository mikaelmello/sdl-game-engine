#ifndef RESOURCES_H
#define RESOURCES_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include <unordered_map>

class Resources {
    public:
        static Mix_Chunk* GetSound(const std::string& file);
        static void ClearSounds();
    private:
        static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};

#endif
