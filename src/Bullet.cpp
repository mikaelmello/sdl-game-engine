#include "Bullet.hpp"
#include "GameObject.hpp"
#include "Helpers.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"
#include "Collider.hpp"
#include <string>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,
    const std::string& sprite, int frameCount, float frameTime)
    : Component(associated), distanceLeft(maxDistance), damage(damage) {
    Sprite* image = new Sprite(associated, sprite, frameCount, frameTime);
    Collider* collider = new Collider(associated);
    associated.AddComponent(image);
    associated.AddComponent(collider);
    associated.angleDeg = Helpers::rad_to_deg(-angle);
    this->speed = Vec2(speed, 0).GetRotated(angle);
}

void Bullet::Update(float dt) {
    Vec2 movement = speed * dt;

    associated.box.x += movement.x;
    associated.box.y += movement.y;

    distanceLeft -= movement.Magnitude();

    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(const std::string& type) const {
    return type == std::string("Bullet");
}

int Bullet::GetDamage() const {
    return damage;
}
