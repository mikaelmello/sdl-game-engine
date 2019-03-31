#ifndef ALIEN_H
#define ALIEN_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Vec2.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>
#include <vector>
#include <queue>
#include <memory>

class Alien : public Component {
    public:
        Alien(GameObject& associated, int nMinions);

        ~Alien();

        void Start();

        void NotifyCollision(GameObject& other) override;

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;

    private:
        class Action {
            public:
                enum ActionType {
                    MOVE,
                    SHOOT,
                };

                Action(ActionType type, float x, float y);

                ActionType type;
                Vec2 pos;
        };

        Vec2 speed;
        int hp;
        int nMinions;

        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minions;
};

#endif
