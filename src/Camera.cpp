#include "Camera.hpp"
#include "Vec2.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Game.hpp"

GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed = {300, 0};

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
    Vec2 x(100, 0);
}

void Camera::Update(float dt) {
    Game& game = Game::GetInstance();
    if (focus != nullptr) {
        pos = focus->box.Center() - Vec2(game.GetWidth() / 2, game.GetHeight() / 2);
        return;
    }

    InputManager& im = InputManager::GetInstance();
    bool right = im.IsKeyDown(RIGHT_ARROW_KEY);
    bool down = im.IsKeyDown(DOWN_ARROW_KEY);
    bool left = im.IsKeyDown(LEFT_ARROW_KEY);
    bool up = im.IsKeyDown(UP_ARROW_KEY);

    Vec2 curSpeed = speed * dt;

    if (right) {
        pos.x += curSpeed.x;
    }
    if (left) {
        pos.x -= curSpeed.x;
    }
    if (up) {
        pos.y -= curSpeed.x;
    }
    if (down) {
        pos.y += curSpeed.x;
    }
}
