#ifndef SOUND_H
#define SOUND_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>

class Sound : public Component {
    public:
        Sound(GameObject& associated);

        Sound(GameObject& associated, const std::string& file);

        ~Sound();

        void Open(const std::string& file);

        void Play(int times = 1);

        void Stop();

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;

        bool IsOpen() const;
    private:
        Mix_Chunk* chunk;
        int channel;
};

#endif
