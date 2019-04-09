#ifndef ALIEN_H
#define ALIEN_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Vec2.hpp"
#include "Component.hpp"
#include "Timer.hpp"
#include "GameObject.hpp"
#include <string>
#include <vector>
#include <queue>
#include <memory>

class Alien : public Component {
    public:
        Alien(GameObject& associated, int nMinions, float timeOffset = 0);

        ~Alien();

        void Start();

        void NotifyCollision(GameObject& other) override;

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;

        static int alienCount;
    private:
        void Shoot();

        static const float restingCooldown;
        enum AlienState { MOVING, RESTING };
        AlienState state;
        Timer restTimer;
        Vec2 destination;
        Vec2 speed;
        int hp;
        int nMinions;
        float timeOffset;

        std::vector<std::weak_ptr<GameObject>> minions;
};

#endif
