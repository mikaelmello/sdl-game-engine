#ifndef COLLIDER_H
#define COLLIDER_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Component.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Rect.hpp"
#include <string>
#include <memory>

class Collider : public Component {
    public:
        Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

        void Update(float dt) override;

        bool Is(GameData::Types type) const override;

        void Render() override;

        void SetScale(Vec2 scale);

        void SetOffset(Vec2 offset);

        Rect box;
    private:
        Vec2 scale;
        Vec2 offset;
};

#endif
