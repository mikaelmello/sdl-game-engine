#define INCLUDE_SDL
#include "SDL_include.h"
#include "InputManager.hpp"
#include <unordered_map>
#include <memory>

InputManager InputManager::instance;

InputManager& InputManager::GetInstance() {
    return instance;
}

InputManager::InputManager() : updateCounter(0), quitRequested(false) {
    mouseX = 0;
    mouseY = 0;
    ::memset(mouseState, 0, sizeof(bool)*6);
    ::memset(mouseUpdate, 0, sizeof(int)*6);
}

InputManager::~InputManager() {}

void InputManager::Update() {
    SDL_Event event;
    updateCounter += 1;

    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        } else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            mouseState[event.button.button] = event.type == SDL_MOUSEBUTTONDOWN;
            mouseUpdate[event.button.button] = updateCounter;
        } else if (!event.key.repeat && (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)) {
            keyState[event.key.keysym.sym] = event.type == SDL_KEYDOWN;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) const {
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) const {
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button) const {
    return mouseState[button];
}

int InputManager::GetMouseX() const {
    return mouseX;
}

int InputManager::GetMouseY() const {
    return mouseY;
}

bool InputManager::QuitRequested() const {
    return quitRequested;
}