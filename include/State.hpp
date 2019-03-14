#ifndef STATE_H
#define STATE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include "Sprite.hpp"

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
