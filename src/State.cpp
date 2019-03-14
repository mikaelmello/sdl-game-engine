#include "State.hpp"
#include <string>
#include <iostream>

State::State() : quitRequested(false), bg("path") {
}

void State::LoadAssets() {
    bg = Sprite("assets/img/ocean.jpg");
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
