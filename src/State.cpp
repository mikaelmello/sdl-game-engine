#include "State.hpp"
#include "Face.hpp"
#include "Sprite.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "InputManager.hpp"
#include "Sound.hpp"
#include "Camera.hpp"
#include "CameraFollower.hpp"
#include <string>
#include <cmath>
#include <algorithm>

State::State() : quitRequested(false) {
    GameObject* go = new GameObject();

    CameraFollower* backgroundFixer = new CameraFollower(*go);
    Sprite* background = new Sprite(*go, "assets/img/ocean.jpg");
    go->box.w = background->GetWidth();
    go->box.h = background->GetHeight();

    music.Open("assets/audio/stageState.ogg");
    music.Play();

    go->AddComponent(backgroundFixer);
    go->AddComponent(background);
    objects.emplace_back(go);

    GameObject* mapGo = new GameObject();
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
    TileMap* map = new TileMap(*mapGo, "assets/map/tileMap.txt", tileSet);
    mapGo->AddComponent(map);
    objects.emplace_back(mapGo);
}

State::~State() {
    objects.clear();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    InputManager& im = InputManager::GetInstance();
    quitRequested |= im.QuitRequested() || im.KeyPress(ESCAPE_KEY);

    if (im.KeyPress(SPACE_BAR_KEY)) {
        Vec2 objPos = Vec2(200, 0).GetRotated( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2(im.GetMouseX() + Camera::pos.x, im.GetMouseY() + Camera::pos.y);
        AddObject((int)objPos.x, (int)objPos.y);
    }

    Camera::Update(dt);

    std::for_each(
        objects.begin(),
        objects.end(),
        [&](auto&& go) { go->Update(dt); }
    );

    objects.erase(
        std::remove_if(
            objects.begin(),
            objects.end(),
            [](auto&& go) { return go->IsDead(); }
        ),
        objects.end()
    );
}

void State::Render() {
    std::for_each(
        objects.begin(),
        objects.end(),
        [&](auto&& go) { go->Render(); }
    );
}

bool State::QuitRequested() const {
    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject* go = new GameObject();
    Sprite* penguinSprite = new Sprite(*go, "assets/img/penguinface.png");

    go->box.x = (float) mouseX - (float) penguinSprite->GetWidth() / 2;
    go->box.y = (float) mouseY - (float) penguinSprite->GetHeight() / 2;
    go->box.w = (float) penguinSprite->GetWidth();
    go->box.h = (float) penguinSprite->GetHeight();

    Sound* penguinSound = new Sound(*go, "assets/audio/boom.wav");
    Face* penguinFace = new Face(*go);

    go->AddComponent(penguinSprite);
    go->AddComponent(penguinSound);
    go->AddComponent(penguinFace);

    objects.emplace_back(go);
}
