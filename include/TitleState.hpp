#ifndef TITLESTATE_H
#define TITLESTATE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "State.hpp"
#include "Music.hpp"

class TitleState : public State {
    public:
        TitleState();

        ~TitleState();

        void Start();

        void Pause();

        void Resume();

        bool QuitRequested() const;

        void LoadAssets();

        void Update(float dt);

        void Render();
};

#endif
