#ifndef STATE_H
#define STATE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL

#include <string>
#include "SDL_include.h"

class State {
    public:
        State();

        bool QuitRequested();

        void LoadAssets();

        void Update(float dt);

        void Render();
    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};

#endif
