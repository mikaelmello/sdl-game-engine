#ifndef BULLET_H
#define BULLET_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Vec2.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>

#define BULLET_SPEED 200

class Bullet : public Component {
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string& sprite);

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;

        int GetDamage() const;
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};

#endif
