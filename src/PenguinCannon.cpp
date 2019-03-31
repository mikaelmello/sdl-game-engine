#include "PenguinBody.hpp"
#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "State.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Helpers.hpp"
#include <string>
#include <cmath>

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), penguinBody(penguinBody), angle(0) {
    Sprite* sprite = new Sprite(associated, "assets/img/cubngun.png");
    Collider* collider = new Collider(associated);
    associated.AddComponent(sprite);
    associated.AddComponent(collider);
}

void PenguinCannon::Update(float dt) {
    InputManager& im = InputManager::GetInstance();
    std::shared_ptr<GameObject> body = penguinBody.lock();
    if (body->IsDead()) {
        associated.RequestDelete();
    }

    Vec2 bodyCenter = body->box.Center();
    associated.box = associated.box.GetCentered(bodyCenter);

    Vec2 mousePos = {
        im.GetMouseX() + Camera::pos.x,
        im.GetMouseY() + Camera::pos.y,
    };

    angle = (mousePos - bodyCenter).XAxisInclination();
    associated.angleDeg = Helpers::rad_to_deg(-angle);

    if (im.MousePress(LEFT_MOUSE_BUTTON)) {
        Shoot();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(const std::string& type) const {
    return type == std::string("PenguinCannon");
}

void PenguinCannon::Shoot() {
    Game& game = Game::GetInstance();
    State& state = game.GetState();

    GameObject* go = new GameObject();
    Bullet* bullet = new Bullet(*go, angle, 400, 30, 500, "assets/img/penguinbullet.png", 4, 0.3, false);

    Vec2 curPos = associated.box.Center();
    Vec2 initialPos = curPos + Vec2(50, 0).GetRotated(angle);
    go->box = go->box.GetCentered(initialPos);
    go->AddComponent(bullet);
    state.AddObject(go);
}
