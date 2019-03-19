#include "Component.hpp"

Component::Component(GameObject& associated) : associated(associated) {}

Component::~Component() {}
