#include "EndState.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Text.hpp"
#include "GameData.hpp"
#include "InputManager.hpp"
#include "TitleState.hpp"

EndState::EndState() {
    GameObject* go = new GameObject();
    Sprite* background;
    if (GameData::playerVictory) {
        background = new Sprite(*go, "assets/img/win.jpg");
        backgroundMusic.Open("assets/audio/endStateWin.ogg");
    } else {
        background = new Sprite(*go, "assets/img/lose.jpg");
        backgroundMusic.Open("assets/audio/endStateLose.ogg");
    }
    go->AddComponent(background);
    objects.emplace_back(go);

    GameObject* titleGo = new GameObject();
    Text* text = new Text(*titleGo, "assets/font/Call me maybe.ttf", 50, Text::TextStyle::BLENDED, "PRESS ESC TO QUIT", { 255, 0, 0, 1 });
    titleGo->AddComponent(text);
    titleGo->box = titleGo->box.GetCentered(512, 400);
    objects.emplace_back(titleGo);

    GameObject* titleGo2 = new GameObject();
    Text* text2 = new Text(*titleGo2, "assets/font/Call me maybe.ttf", 50, Text::TextStyle::BLENDED, "PRESS SPACE TO RESTART", { 255, 127, 0, 1 });
    text2->SetBlink(true, 0.5);
    titleGo2->AddComponent(text2);
    titleGo2->box = titleGo2->box.GetCentered(512, 500);
    objects.emplace_back(titleGo2);
}

EndState::~EndState() {}

void EndState::Update(float dt) {
    if (quitRequested || popRequested) {
        return;
    }

    InputManager& im = InputManager::GetInstance();

    UpdateArray(dt);

    if (im.IsKeyDown(ESCAPE_KEY)) {
        quitRequested = true;
        return;
    }

    if (im.IsKeyDown(SPACE_BAR_KEY)) {
        popRequested = true;
    }
}

void EndState::Start() {
    backgroundMusic.Play();
    LoadAssets();
    StartArray();
    started = true;
}

void EndState::Pause() {}

void EndState::Resume() {
    Camera::pos = {0, 0};
}

void EndState::LoadAssets() {}

void EndState::Render() {
    RenderArray();
}
