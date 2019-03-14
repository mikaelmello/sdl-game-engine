#ifndef MUSIC_H
#define MUSIC_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include <string>

class Music {
    public:
        Music();

        Music(std::string file);

        ~Music();

        void Play(int times);
        void Stop(int msToStop);
        void Open(std::string file);
        bool IsOpen();
    private:
        Mix_Music* music;
};

#endif
