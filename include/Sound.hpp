#ifndef SOUND_H
#define SOUND_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include <string>
#include "SDL_include.h"
#include "Component.hpp"
#include "GameObject.hpp"

class Sound : public Component {
    public:
        Sound(GameObject& associated);

        Sound(GameObject& associated, const std::string& file);

        ~Sound();

        void Open(const std::string& file);

        void Play(int times = 1);

        void Stop();

        void Update(float dt);

        bool Is(const std::string& type);

        void Render();

        bool IsOpen() const;
    private:
        Mix_Chunk* chunk;
        int channel;
};

#endif
