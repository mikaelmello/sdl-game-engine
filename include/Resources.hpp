#ifndef RESOURCES_H
#define RESOURCES_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <string>
#include <unordered_map>

class Resources {
    public:
        static SDL_Texture* GetImage(const std::string& file);
        static Mix_Chunk* GetSound(const std::string& file);
        static Mix_Music* GetMusic(const std::string& file);
        static void ClearImages();
        static void ClearSounds();
        static void ClearMusics();
    private:
        static std::unordered_map<std::string, SDL_Texture*> imageTable;
        static std::unordered_map<std::string, Mix_Music*> musicTable;
        static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};

#endif
