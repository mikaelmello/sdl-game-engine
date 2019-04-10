#include "StageState.hpp"
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
#include "PenguinBody.hpp"
#include "Vec2.hpp"
#include "Music.hpp"
#include "Helpers.hpp"
#include "Collision.hpp"
#include "Collider.hpp"
#include "GameData.hpp"
#include "EndState.hpp"
#include "Game.hpp"
#include <string>
#include <cmath>
#include <algorithm>
#include <memory>

StageState::StageState() : State() {
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

    Vec2 alienPositions[] = { {0, 0}, {0, 1280}, {1408, 0}, {1408, 1280} };
    float alienOffsets[] = { -0.32, 0.57, 0, 2.142};
    for (int i = 0; i < 4; i++) {
        GameObject* alienGo = new GameObject();
        Alien* alien = new Alien(*alienGo, 4, alienOffsets[i]);
        alienGo->AddComponent(alien);
        alienGo->box = alienGo->box.GetCentered(alienPositions[i]);
        objects.emplace_back(alienGo);
    }

    GameObject* penguinGo = new GameObject();
    PenguinBody* pb = new PenguinBody(*penguinGo);
    penguinGo->AddComponent(pb);
    penguinGo->box = penguinGo->box.GetCentered(704, 640);
    objects.emplace_back(penguinGo);
    
    Camera::Follow(penguinGo);

    music.Open("assets/audio/stageState.ogg");
}

void StageState::Start() {
    started = true;
	music.Play();
    LoadAssets();
    StartArray();
}

void StageState::Pause() {
    music.Stop(0);
}

void StageState::Resume() {
    music.Play();
}

StageState::~StageState() {
    music.Stop(0);
	delete tileSet;
}

void StageState::LoadAssets() {
}

void StageState::Update(float dt) {
    if (quitRequested || popRequested) {
        return;
    }

    InputManager& im = InputManager::GetInstance();
    quitRequested |= im.QuitRequested();
    popRequested |= im.KeyPress(ESCAPE_KEY);

    Camera::Update(dt);

    UpdateArray(dt);

    for (int i = 0; i < objects.size(); i++) {
        for (int j = i+1; j < objects.size(); j++) {
            std::shared_ptr<GameObject> go1 = objects[i];
            std::shared_ptr<GameObject> go2 = objects[j];

            auto colliderSp1 = go1->GetComponent("Collider").lock();
            auto colliderSp2 = go2->GetComponent("Collider").lock();
            
            if (!colliderSp1 || !colliderSp2) {
                continue;
            }

            auto collider1 = std::dynamic_pointer_cast<Collider>(colliderSp1);
            auto collider2 = std::dynamic_pointer_cast<Collider>(colliderSp2);

            float radDeg1 = Helpers::deg_to_rad(go1->angleDeg);
            float radDeg2 = Helpers::deg_to_rad(go2->angleDeg);
            bool collides = Collision::IsColliding(collider1->box, collider2->box, radDeg1, radDeg2);
            if (collides) {
                go1->NotifyCollision(*go2);
                go2->NotifyCollision(*go1);
            }
        }
    }

    objects.erase(
        std::remove_if(
            objects.begin(),
            objects.end(),
            [](std::shared_ptr<GameObject>& go) { return go->IsDead(); }
        ),
        objects.end()
    );

    if (PenguinBody::player == nullptr || Alien::alienCount == 0) {
        GameData::playerVictory = PenguinBody::player != nullptr;
        popRequested = true;
        Game& game = Game::GetInstance();
        EndState* endState = new EndState();
        game.Push(endState);
    }
}

void StageState::Render() {
    RenderArray();
}

