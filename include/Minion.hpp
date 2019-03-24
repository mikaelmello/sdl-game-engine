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

#define MINION_SPEED (M_PI / 2)
#define MINION_DISTANCE (150)

class Minion : public Component {
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;

        void Shoot (Vec2 target);
    private:
        std::weak_ptr<GameObject> alienCenter;
        float arc;
};

#endif
