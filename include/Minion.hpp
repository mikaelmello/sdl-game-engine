#ifndef MINION_H
#define MINION_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Vec2.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>
#include <memory>
#include <cmath>

class Minion : public Component {
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;

        void Shoot (Vec2 target);

        const static float rotationSpeed;
    private:
        const static float distanceFromCenter;
        std::weak_ptr<GameObject> alienCenter;
        float arc;
};

#endif
