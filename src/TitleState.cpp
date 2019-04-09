#include "TitleState.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "StageState.hpp"

TitleState::TitleState() {
    GameObject* go = new GameObject();
    Sprite* title = new Sprite(*go, "assets/img/title.jpg");
    go->AddComponent(title);
    objects.emplace_back(go);
}

TitleState::~TitleState() {}

void TitleState::Update(float dt) {
    InputManager& im = InputManager::GetInstance();

    UpdateArray(dt);

    if (im.IsKeyDown(ESCAPE_KEY)) {
        quitRequested = true;
        return;
    }

    if (im.IsKeyDown(SPACE_BAR_KEY) || im.QuitRequested()) {
        Game& game = Game::GetInstance();
        StageState* stageState = new StageState();
        game.Push(stageState);
    }
}

void TitleState::Start() {
    LoadAssets();
    StartArray();
    started = true;
}

void TitleState::Pause() {}

void TitleState::Resume() {
    Camera::pos = {0, 0};
}

void TitleState::LoadAssets() {}

void TitleState::Render() {
    RenderArray();
}