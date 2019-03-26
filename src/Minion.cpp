#include "Minion.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Game.hpp"
#include "State.hpp"
#include "Bullet.hpp"
#include "Helpers.hpp"
#include <string>
#include <cmath>

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
    arc = fmod(arc + distanceToMove, M_PI * 2);
    Vec2 movement = Vec2(MINION_DISTANCE, 0).GetRotated(arc);
    Vec2 newPos = alienCenterGo->box.Center() + movement;

    associated.box.x = newPos.x - associated.box.w/2;
    associated.box.y = newPos.y - associated.box.h/2;
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

    Bullet* bullet = new Bullet(*go, direction.XAxisInclination(), 400, 30, 500, "assets/img/minionbullet1.png");
    go->AddComponent(bullet);
    go->box.x = curPos.x - go->box.w / 2;
    go->box.y = curPos.y - go->box.h / 2;

    state.AddObject(go);
}
