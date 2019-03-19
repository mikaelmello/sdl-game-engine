#include "State.hpp"
#include <string>
#include <iostream>

State::State() : quitRequested(false), bg("assets/img/ocean.jpg") {
    try {
        // wrapping it in a try-catch because music is not really necessary for the game to run
        // even though we would need to get maximum grades, there is no reason to exit the program
        music.Open("assets/audio/stageState.ogg");
        music.Play();
    } catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
        std::cout << "Could not play Stage State music, exception description:\n\n" << ex.what() << std::endl;
    }
}

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

bool State::QuitRequested() const {
    return quitRequested;
}
