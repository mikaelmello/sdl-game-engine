#include "Collider.hpp"
#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Game.hpp"
#include "State.hpp"
#include "InputManager.hpp"
#include "Helpers.hpp"
#include <string>
#include <cmath>

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset) {
}

void Collider::Update(float dt) {
    box = associated.box;
    box.w *= scale.x;
    box.y *= scale.y;
    box = box.GetCentered(associated.box.Center());

    box += offset.GetRotated(associated.angleDeg);
}

void Collider::Render() {}

bool Collider::Is(const std::string& type) const {
    return type == std::string("Collider");
}

void Collider::SetOffset(Vec2 offset) {
    offset = offset;
}

void Collider::SetScale(Vec2 scale) {
    scale = scale;
}
