#include "TitleState.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Text.hpp"
#include "InputManager.hpp"
#include "StageState.hpp"

TitleState::TitleState() {
    GameObject* go = new GameObject();
    Sprite* title = new Sprite(*go, "assets/img/title.jpg");
    go->AddComponent(title);
    objects.emplace_back(go);

    GameObject* titleGo = new GameObject();
    Text* text = new Text(*titleGo, "assets/font/Call me maybe.ttf", 50, Text::TextStyle::BLENDED, "PRESS SPACE TO CONTINUE", { 255, 127, 0, 1 });
    text->SetBlink(true, 0.5);
    titleGo->AddComponent(text);
    titleGo->box = titleGo->box.GetCentered(512, 400);
    objects.emplace_back(titleGo);
}

TitleState::~TitleState() {}

void TitleState::Update(float dt) {
    if (quitRequested || popRequested) {
        return;
    }

    InputManager& im = InputManager::GetInstance();

    UpdateArray(dt);

    if (im.IsKeyDown(ESCAPE_KEY) || im.QuitRequested()) {
        quitRequested = true;
        return;
    }

    if (im.IsKeyDown(SPACE_BAR_KEY)) {
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