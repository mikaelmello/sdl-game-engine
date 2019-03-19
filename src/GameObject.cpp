#include "GameObject.hpp"
#include <memory>
#include <vector>
#include <algorithm>

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Render();
    }
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::find_if(components.begin(), components.end(),
        [&](std::unique_ptr<Component>& obj){ return obj.get() == cpt; });

    if (it != components.end()) {
        components.erase(it);
    }
}

Component* GameObject::GetComponent(const std::string& type) {
    auto it = std::find_if(components.begin(), components.end(),
        [&](std::unique_ptr<Component>& obj){ return obj->Is(type); });

    if (it == components.end()) {
        return nullptr;
    }

    return (*it).get();
}
