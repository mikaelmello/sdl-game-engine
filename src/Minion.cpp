#include "Minion.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include <string>

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg) {
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent(sprite);
}

void Minion::Update(float dt) {
    std::shared_ptr<GameObject> alienCenterGo = alienCenter.lock();

    if (!alienCenterGo) {
        associated.RequestDelete();
        return;
    }

    float distanceToMove = MINION_SPEED * dt;
    arc += distanceToMove;
    Vec2 movement = Vec2(MINION_DISTANCE, 0).GetRotated(arc);
    Vec2 newPos = alienCenterGo->box.Center() + movement;

    associated.box.x = newPos.x - associated.box.w/2;
    associated.box.y = newPos.y - associated.box.h/2;
}

void Minion::Render() {}

bool Minion::Is(const std::string& type) const {
    return type == std::string("Minion");
}
