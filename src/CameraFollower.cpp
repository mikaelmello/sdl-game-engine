#include "CameraFollower.hpp"
#include "Camera.hpp"
#include "GameData.hpp"
#include <string>

CameraFollower::CameraFollower(GameObject& associated) : Component(associated) {}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render() {}

bool CameraFollower::Is(GameData::Types type) const {
    return type == GameData::Types::CameraFollower;
}
