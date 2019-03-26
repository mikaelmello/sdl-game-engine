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
#include "Alien.hpp"
#include "Vec2.hpp"
#include "Music.hpp"
#include <string>
#include <cmath>
#include <algorithm>
#include <memory>

State::State() : quitRequested(false), started(false) {
    GameObject* go = new GameObject();
    CameraFollower* backgroundFixer = new CameraFollower(*go);
    Sprite* background = new Sprite(*go, "assets/img/ocean.jpg");
    go->AddComponent(backgroundFixer);
    go->AddComponent(background);
    objects.emplace_back(go);

    GameObject* mapGo = new GameObject();
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
    TileMap* map = new TileMap(*mapGo, "assets/map/tileMap.txt", tileSet);
    map->SetParallax(1, 0.5, 0.5);
    mapGo->AddComponent(map);
    objects.emplace_back(mapGo);

    GameObject* alienGo = new GameObject();
    Alien* alien = new Alien(*alienGo, 4);
    alienGo->AddComponent(alien);
    alienGo->box.x = 512 - alienGo->box.w / 2;
    alienGo->box.y = 300 - alienGo->box.h / 2;
    objects.emplace_back(alienGo);

    music.Open("assets/audio/stageState.ogg");
	music.Play();
}

void State::Start() {
    LoadAssets();

    std::for_each(
        objects.begin(),
        objects.end(),
        [&](std::shared_ptr<GameObject>& go) { go->Start(); }
    );

    started = true;
}

State::~State() {
    objects.clear();
    newObjects.clear();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    InputManager& im = InputManager::GetInstance();
    quitRequested |= im.QuitRequested() || im.KeyPress(ESCAPE_KEY);

    Camera::Update(dt);

    // Since we are using iterators everywhere to iterate through the
    // vectors, we can't add objects in State::AddObject directly into
    // 'objects'. State::AddObject is called from inside a Update function
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

    objects.erase(
        std::remove_if(
            objects.begin(),
            objects.end(),
            [](std::shared_ptr<GameObject>& go) { return go->IsDead(); }
        ),
        objects.end()
    );
}

void State::Render() {
    std::for_each(
        objects.begin(),
        objects.end(),
        [&](std::shared_ptr<GameObject>& go) { go->Render(); }
    );
}

bool State::QuitRequested() const {
    return quitRequested;
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
