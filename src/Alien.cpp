#include "Alien.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Collider.hpp"
#include "State.hpp"
#include "Vec2.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Sound.hpp"
#include "Minion.hpp"
#include "PenguinBody.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <cmath>
#include <queue>

const float Alien::restingCooldown = 1;
int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated), nMinions(nMinions), speed(300, 0), hp(200), state(AlienState::RESTING) {
    Sprite* sprite = new Sprite(associated, "assets/img/alien.png");
    Collider* collider = new Collider(associated);
    associated.AddComponent(sprite);
    associated.AddComponent(collider);
    alienCount++;
}

Alien::~Alien() {
    alienCount--;
    minions.clear();
}

void Alien::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");

    if (bullet != nullptr && !bullet->targetsPlayer) {
        hp -= bullet->GetDamage();
    }
}

void Alien::Start() {
    Game& game = Game::GetInstance();
    State& state = game.GetCurrentState();

    for (int i = 0; i < nMinions; i++) {
        GameObject* minionGo = new GameObject();
        float arc = M_PI * 2 * i / nMinions;
        Minion* minion = new Minion(*minionGo, state.GetObjectPtr(&associated), arc);
        minionGo->AddComponent(minion);
        
        std::weak_ptr<GameObject> minionGoSharedPtr = state.AddObject(minionGo);
        minions.push_back(minionGoSharedPtr);
    }
}

void Alien::Update(float dt) {
    if (hp <= 0) {
        associated.RequestDelete();

        GameObject* explosion = new GameObject();
        Sprite* explosionSprite = new Sprite(*explosion, "assets/img/aliendeath.png", 4, 0.375, 1.5);
        Sound* explosionSound = new Sound(*explosion, "assets/audio/boom.wav");

        explosionSound->Play();
        explosion->AddComponent(explosionSound);
        explosion->AddComponent(explosionSprite);
        explosion->box = explosion->box.GetCentered(associated.box.Center());
        Game::GetInstance().GetCurrentState().AddObject(explosion);
        return;
    }

    restTimer.Update(dt);
    associated.angleDeg = fmod(associated.angleDeg + 10 * Minion::rotationSpeed * dt, 360);
    PenguinBody* player = PenguinBody::player;

    Vec2 curPos = associated.box.Center();
    if (state == AlienState::MOVING) {
        if (curPos.Distance(destination) < speed.Magnitude() * dt) {
            associated.box = associated.box.GetCentered(destination);
            state = AlienState::RESTING;
            restTimer.Restart();
            Shoot();
        } else {
            associated.box += speed * dt;
        }
    } else if (state == AlienState::RESTING && player && restTimer.Get() >= restingCooldown) {
        destination = player->GetPosition();
        float direction = (destination - curPos).XAxisInclination();
        speed = Vec2(speed.Magnitude(), 0).GetRotated(direction);
        state = AlienState::MOVING;
    }
}

void Alien::Shoot() {
    float minDistance = 1e15; // arbitrarily large number
    int minionIndex = -1;

    PenguinBody* player = PenguinBody::player;
    if (player == nullptr) {
        return;
    }

    Vec2 target = player->GetPosition();

    for (int i = 0; i < nMinions; i++) {
        std::shared_ptr<GameObject> minion = minions[i].lock();
        float distance = target.Distance(minion->box.Center());
        if (distance <= minDistance) {
            minDistance = distance;
            minionIndex = i;
        }
    }
    Minion* minion = (Minion*) minions[minionIndex].lock()->GetComponent("Minion");
    minion->Shoot(target);
}

void Alien::Render() {}

bool Alien::Is(const std::string& type) const {
    return type == std::string("Alien");
}
