#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.hpp"
#include <string>
#include <iostream>

State::State() : quitRequested(false), bg("path") {
}

void State::LoadAssets() {

}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg.Render();
}

bool State::QuitRequested() {
    return quitRequested;
}
