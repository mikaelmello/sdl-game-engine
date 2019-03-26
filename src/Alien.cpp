#include "Alien.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "State.hpp"
#include "Vec2.hpp"
#include "Camera.hpp"
#include "Minion.hpp"
#include <string>
#include <memory>
#include <cmath>
#include <queue>

Alien::Alien(GameObject& associated, int nMinions) : Component(associated), nMinions(nMinions) {
    Sprite* sprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(sprite);
}

Alien::~Alien() {
    minions.clear();
}

void Alien::Start() {
    Game& game = Game::GetInstance();
    State& state = game.GetState();

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
        return;
    }

    InputManager& im = InputManager::GetInstance();

    Vec2 mousePos = {
        im.GetMouseX() + Camera::pos.x,
        im.GetMouseY() + Camera::pos.y,
    };

    associated.angleDeg = fmod(associated.angleDeg + 10 * MINION_SPEED * dt, 360);

    if (im.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.emplace(Action::SHOOT, mousePos.x, mousePos.y);
    }
    if (im.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.emplace(Action::MOVE, mousePos.x, mousePos.y);
    }

    if (!taskQueue.empty()) {
        Action act = taskQueue.front();
        float distanceToMove = ALIEN_SPEED * 0.034;

        if (act.type == Action::MOVE) {
            Vec2 curPos = associated.box.Center();
            Vec2 tarPos = act.pos;
            Vec2 direction = tarPos - curPos;
            Vec2 movement = Vec2(distanceToMove, 0).GetRotated(direction.XAxisInclination());

            if (curPos.Distance(tarPos) < distanceToMove) {
                associated.box = associated.box.GetCentered(tarPos);
                taskQueue.pop();
            } else {
                associated.box.x += movement.x;
                associated.box.y += movement.y;
            }
        } else if (act.type == Action::SHOOT) {
            float minDistance = 1e15; // arbitrarily large number
            int minionIndex = -1;

            for (int i = 0; i < nMinions; i++) {
                std::shared_ptr<GameObject> minion = minions[i].lock();
                float distance = act.pos.Distance(minion->box.Center());
                if (distance <= minDistance) {
                    minDistance = distance;
                    minionIndex = i;
                }
            }
            Minion* minion = (Minion*) minions[minionIndex].lock()->GetComponent("Minion");
            minion->Shoot(act.pos);
            taskQueue.pop();
        }
    }
}

void Alien::Render() {}

bool Alien::Is(const std::string& type) const {
    return type == std::string("Alien");
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type), pos(x, y) {}
