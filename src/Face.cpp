#include "Face.hpp"
#include "Sound.hpp"
#include "InputManager.hpp"
#include <string>

Face::Face(GameObject& associated) : Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        Sound* sound = (Sound *) associated.GetComponent("Sound");
        if (sound != nullptr) {
            sound->Play();
        }
    }
}

void Face::Update(float dt) {
    InputManager& im = InputManager::GetInstance();
    if (im.IsMouseDown(LEFT_MOUSE_BUTTON)) {
        if (associated.box.Contains({ (float) im.GetMouseX(), (float) im.GetMouseY() })) {
            Damage(std::rand() % 10 + 10);
        }
    }
}

void Face::Render() {}

bool Face::Is(const std::string& type) const {
    return type == std::string("Face");
}
