#ifndef STATE_H
#define STATE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "GameObject.hpp"
#include "TileSet.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include <string>
#include <vector>
#include <memory>

class State {
    public:
        State();

        ~State();

        void Start();

        std::weak_ptr<GameObject> AddObject(GameObject* go);

        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

        bool QuitRequested() const;

        void LoadAssets();

        void Update(float dt);

        void Render();
    private:
        std::vector<std::shared_ptr<GameObject>> objects;
        bool started;
        Music music;
        TileSet* tileSet;
        bool quitRequested;
};

#endif
