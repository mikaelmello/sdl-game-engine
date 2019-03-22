#include "Face.hpp"
#include "Sound.hpp"
#include "GameObject.hpp"
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

void Face::Update(float dt) {}

void Face::Render() {}

bool Face::Is(const std::string& type) const {
    return type == std::string("Face");
}
