#include "State.hpp"
#include <string>
#include <iostream>

State::State() : quitRequested(false), bg("assets/img/ocean.jpg"), music("assets/audio/stageState.ogg") {}

void State::LoadAssets() {
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}
