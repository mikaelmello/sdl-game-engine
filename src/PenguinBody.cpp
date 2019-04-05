#include "PenguinBody.hpp"
#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "Sound.hpp"
#include "Game.hpp"
#include "State.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Helpers.hpp"
#include <string>
#include <cmath>

float PenguinBody::maxSpeed = 400;
float PenguinBody::maxReverseSpeed = 100;
float PenguinBody::acceleration = 100;
float PenguinBody::angleSpeed = M_PI * 2;
PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated), speed(0, 0), linearSpeed(0), angle(0), hp(100) {
    Collider* collider = new Collider(associated);
    Sprite* sprite = new Sprite(associated, "assets/img/penguin.png");
    associated.AddComponent(collider);
    associated.AddComponent(sprite);
    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");

    if (bullet != nullptr && bullet->targetsPlayer) {
        hp -= bullet->GetDamage();
    }
}

void PenguinBody::Start() {
    Game& game = Game::GetInstance();
    State& state = game.GetCurrentState();
    GameObject* go = new GameObject();
    PenguinCannon* pc = new PenguinCannon(*go, state.GetObjectPtr(&associated));
    go->AddComponent(pc);
    penguinCannon = state.AddObject(go);
}

void PenguinBody::Update(float dt) {
    std::shared_ptr<GameObject> pcGo = penguinCannon.lock();
    InputManager& im = InputManager::GetInstance();
    linearSpeed = speed.x;

    if (im.IsKeyDown(W_KEY)) {
        linearSpeed = std::min(linearSpeed + acceleration * dt, maxSpeed);
    }
    if (im.IsKeyDown(S_KEY)) {
        linearSpeed = std::max(linearSpeed - acceleration * dt, -maxReverseSpeed);
    }
    if (im.IsKeyDown(A_KEY)) {
        angle -= angleSpeed * (1 - (abs(linearSpeed) / (2 * maxSpeed))) * dt;
    }
    if (im.IsKeyDown(D_KEY)) {
        angle += angleSpeed * (1 - (abs(linearSpeed) / (2 * maxSpeed))) * dt;
    }

    speed = { linearSpeed, 0 };
    Vec2 movement = speed.GetRotated(angle) * dt;
    associated.box += movement;
    associated.angleDeg = Helpers::rad_to_deg(angle);

    if (hp <= 0) {
        associated.RequestDelete();
        pcGo->RequestDelete();
        Camera::Unfollow();

        GameObject* explosion = new GameObject();
        Sprite* explosionSprite = new Sprite(*explosion, "assets/img/penguindeath.png", 5, 0.3, 1.5);
        Sound* explosionSound = new Sound(*explosion, "assets/audio/boom.wav");

        explosionSound->Play();
        explosion->AddComponent(explosionSound);
        explosion->AddComponent(explosionSprite);
        explosion->box = explosion->box.GetCentered(associated.box.Center());
        Game::GetInstance().GetCurrentState().AddObject(explosion);
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(const std::string& type) const {
    return type == std::string("PenguinBody");
}

Vec2 PenguinBody::GetPosition() {
    return associated.box.Center();
}
