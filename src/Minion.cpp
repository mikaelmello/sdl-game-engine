#include "Minion.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Game.hpp"
#include "Collider.hpp"
#include "State.hpp"
#include "Bullet.hpp"
#include "Helpers.hpp"
#include <string>
#include <cmath>

const float Minion::rotationSpeed = (M_PI / 2);
const float Minion::distanceFromCenter = 150;

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg) {
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    Collider* collider = new Collider(associated);
    associated.AddComponent(sprite);
    associated.AddComponent(collider);
}

void Minion::Update(float dt) {
    std::shared_ptr<GameObject> alienCenterGo = alienCenter.lock();

    if (!alienCenterGo) {
        associated.RequestDelete();

        GameObject* explosion = new GameObject();
        Sprite* explosionSprite = new Sprite(*explosion, "assets/img/miniondeath.png", 4, 0.375, 1.5);
        explosion->AddComponent(explosionSprite);
        explosion->box = explosion->box.GetCentered(associated.box.Center());
        Game::GetInstance().GetState().AddObject(explosion);
        return;
    }

    float distanceToMove = rotationSpeed * dt;
    arc = fmod(arc + distanceToMove, M_PI * 2);
    Vec2 movement = Vec2(distanceFromCenter, 0).GetRotated(arc);
    Vec2 newPos = alienCenterGo->box.Center() + movement;

    associated.box = associated.box.GetCentered(newPos);
    associated.angleDeg = Helpers::rad_to_deg(arc);
}

void Minion::Render() {}

bool Minion::Is(const std::string& type) const {
    return type == std::string("Minion");
}

void Minion::Shoot(Vec2 target) {
    Game& game = Game::GetInstance();
    State& state = game.GetState();

    Vec2 curPos = associated.box.Center();
    Vec2 direction = target - curPos;

    GameObject* go = new GameObject();

    float bulletSpeed = 400;
    float bulletDamage = rand() % 10 + 20;
    float bulletDistance = 500;
    Bullet* bullet = new Bullet(*go, direction.XAxisInclination(), bulletSpeed, bulletDamage,
        bulletDistance, "assets/img/minionbullet2.png", 3, 0.1, true);

    go->box = go->box.GetCentered(curPos);
    go->AddComponent(bullet);
    state.AddObject(go);
}
