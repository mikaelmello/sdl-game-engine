#ifndef PENGUINBODY_H
#define PENGUINBODY_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Component.hpp"
#include "GameObject.hpp"
#include <string>
#include <memory>
#include <cmath>

class PenguinBody : public Component {
    public:
        PenguinBody(GameObject& associated);

        ~PenguinBody();

        void Start();

        void NotifyCollision(GameObject& other) override;

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;

        static PenguinBody* player;
    private:
        static float maxSpeed;
        static float maxReverseSpeed;
        static float acceleration;
        static float angleSpeed;
        Vec2 speed;
        std::weak_ptr<GameObject> penguinCannon;
        float linearSpeed;
        float angle;
        int hp;
};

#endif
