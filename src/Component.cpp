#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(GameObject& associated) : associated(associated) {}

Component::~Component() {}
