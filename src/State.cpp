#include "State.hpp"
#include "Sprite.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "InputManager.hpp"
#include "Sound.hpp"
#include "Camera.hpp"
#include "CameraFollower.hpp"
#include "GameObject.hpp"
#include "Component.hpp"
#include "Vec2.hpp"
#include "Music.hpp"
#include "Helpers.hpp"
#include "Collision.hpp"
#include "Collider.hpp"
#include <string>
#include <cmath>
#include <algorithm>
#include <memory>

State::State() : quitRequested(false), started(false), popRequested(false) {}

State::~State() {
    objects.clear();
    newObjects.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> goSharedPtr(go);
    newObjects.push_back(goSharedPtr);

    if (started) {
        goSharedPtr->Start();
    }

    return std::weak_ptr<GameObject>(goSharedPtr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    auto it = std::find_if(objects.begin(), objects.end(),
        [&](std::shared_ptr<GameObject>& go2){ return go == go2.get(); });

    if (it == objects.end()) {
        return std::weak_ptr<GameObject>();
    }

    return std::weak_ptr<GameObject>(*it);
}

bool State::QuitRequested() const {
    return quitRequested;
}

bool State::PopRequested() const {
    return popRequested;
}

void State::StartArray() {
    std::for_each(
        objects.begin(),
        objects.end(),
        [&](std::shared_ptr<GameObject>& go) { go->Start(); }
    );
}

void State::UpdateArray(float dt) {
    // Since we are using iterators everywhere to iterate through the
    // vectors, we can't add objects in StageState::AddObject directly into
    // 'objects'. StageState::AddObject is called from inside a Update function
    // thus adding a new GameObject while we are iterating through the array,
    // potentially invalidating the iterators and causing a segmentation fault.
    //
    // We add a temporary vector to store new objects and copy then before
    // starting a new set of iterations
    objects.insert(objects.end(), newObjects.begin(), newObjects.end());
    newObjects.clear();

    std::for_each(
        objects.begin(),
        objects.end(),
        [&](std::shared_ptr<GameObject>& go) { go->Update(dt); }
    );
}

void State::RenderArray() {
    std::for_each(
        objects.begin(),
        objects.end(),
        [](std::shared_ptr<GameObject>& go) { go->Render(); }
    );
}
