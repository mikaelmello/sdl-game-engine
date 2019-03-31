#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(GameObject& associated) : associated(associated) {}

Component::~Component() {}

void Component::Start() {}

void Component::NotifyCollision(GameObject& other) {}