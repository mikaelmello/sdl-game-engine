#ifndef ENDSTATE_H
#define ENDSTATE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "State.hpp"
#include "Music.hpp"

class EndState : public State {
    public:
        EndState();

        ~EndState();

        void Start();

        void Pause();

        void Resume();

        bool QuitRequested() const;

        void LoadAssets();

        void Update(float dt);

        void Render();
    private:
        Music backgroundMusic;
};

#endif
