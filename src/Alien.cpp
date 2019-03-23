#include "Alien.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <string>
#include <queue>

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    Sprite* sprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(sprite);
}

Alien::~Alien() {}

void Alien::Start() {}

void Alien::Update(float dt) {
    if (hp <= 0) {
        associated.RequestDelete();
        return;
    }

    InputManager& im = InputManager::GetInstance();

    Vec2 mousePos = {
        im.GetMouseX() - Camera::pos.x,
        im.GetMouseY() - Camera::pos.y,
    };


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
            Vec2 movement = Vec2(distanceToMove, 0).GetRotated(-direction.XAxisInclination());

            if (curPos.Distance(tarPos) < distanceToMove) {
                associated.box.x = tarPos.x - associated.box.w / 2;
                associated.box.y = tarPos.y - associated.box.h / 2;
                taskQueue.pop();
            } else {
                associated.box.x += movement.x;
                associated.box.y += movement.y;
            }
        } else if (act.type == Action::SHOOT) {
            taskQueue.pop();
        }
    }
}

void Alien::Render() {}

bool Alien::Is(const std::string& type) const {
    return type == std::string("Alien");
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type), pos(x, y) {}
