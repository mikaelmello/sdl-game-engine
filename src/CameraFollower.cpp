#include "CameraFollower.hpp"
#include "Camera.hpp"
#include <string>

CameraFollower::CameraFollower(GameObject& associated) : Component(associated) {}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render() {}

bool CameraFollower::Is(const std::string& type) const {
    return type == std::string("CameraFollower");
}
