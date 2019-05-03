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
#include <set>

class State {
    public:
        State();

        virtual ~State();

        virtual void LoadAssets() = 0;

        virtual void Update(float dt) = 0;

        virtual void Render() = 0;

        virtual void Start() = 0;
        
        virtual void Pause() = 0;

        virtual void Resume() = 0;

        virtual std::weak_ptr<GameObject> AddObject(GameObject* go);

        virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

        bool QuitRequested() const;

        bool PopRequested() const;
    protected:
        void StartArray();

        virtual void UpdateArray(float dt);

        virtual void RenderArray();

        bool popRequested;
        bool quitRequested;
        bool started;

        struct GameObjectComp {
            bool operator()(const std::shared_ptr<GameObject>& lhs, const std::shared_ptr<GameObject>& rhs) const {
                return lhs->priority < rhs->priority;
            }
        };

        std::multiset<std::shared_ptr<GameObject>, GameObjectComp> objects;
};

#endif
