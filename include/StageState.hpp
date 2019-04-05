#ifndef STAGESTATE_H
#define STAGESTATE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "GameObject.hpp"
#include "TileSet.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "State.hpp"
#include <string>
#include <vector>
#include <memory>

class StageState : public State {
    public:
        StageState();

        ~StageState();

        void Start();

        void Pause();

        void Resume();

        bool QuitRequested() const;

        void LoadAssets();

        void Update(float dt);

        void Render();
    private:
        Music music;
        TileSet* tileSet;
};

#endif
