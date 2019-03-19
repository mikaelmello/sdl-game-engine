#ifndef STATE_H
#define STATE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include "Sprite.hpp"
#include "Music.hpp"

class State {
    public:
        State();

        bool QuitRequested() const;

        void LoadAssets();

        void Update(float dt);

        void Render();
    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};

#endif
