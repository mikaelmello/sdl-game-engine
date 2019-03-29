#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Resources.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include <stdexcept>
#include <string>
#include <iostream>

Sprite::Sprite(GameObject& associated, int frameCount, float frameTime)
    : Component(associated), texture(nullptr), scale(1, 1), frameCount(frameCount), frameTime(frameTime), currentFrame(0), timeElapsed(0) {}

Sprite::Sprite(GameObject& associated, const std::string& file, int frameCount, float frameTime) : Sprite(associated, frameCount, frameTime) {
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(const std::string& file) {
    texture = Resources::GetImage(file);
    int return_code = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    if (return_code != 0) {
        throw std::runtime_error("Could not query invalid texture from " + file + ": " + IMG_GetError());
    }

    associated.box.w = width;
    associated.box.h = height;
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = { x, y, w, h };
}

void Sprite::Render(int x, int y) {
    SDL_Rect temp_rect = { x, y,  (int) round(scale.x * clipRect.w), (int) round(scale.y * clipRect.h) };
    int return_code = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &temp_rect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (return_code != 0) {
        throw std::runtime_error("Could not copy sprite to rendering target: " + std::string(IMG_GetError()));
    }
}

void Sprite::Render() {
    Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Update(float dt) {
    timeElapsed += dt;
    if (timeElapsed > frameTime) {
        int framesElapsed = timeElapsed / frameTime;
        int nextFrame = (currentFrame + framesElapsed) % frameCount;
        SetFrame(nextFrame);
        timeElapsed = 0;
    }
}

bool Sprite::Is(const std::string& type) const {
    return type == std::string("Sprite");
}

int Sprite::GetWidth() const {
    return round(scale.x * (width / frameCount));
}

int Sprite::GetHeight() const {
    return round(scale.y * height);
}

bool Sprite::IsOpen() const {
    return texture != nullptr;
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
    Vec2 oldCenter = associated.box.Center();

    if (scaleX != 0) {
        scale.x = scaleX;
        associated.box.w = GetWidth();
    }
    if (scaleY != 0) {
        scale.y = scaleY;
        associated.box.h = GetHeight();
    }

    associated.box = associated.box.GetCentered(oldCenter);
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    SetClip(currentFrame * width / frameCount, 0, width / frameCount, height);
}

void Sprite::SetFrameCount(int frameCount) {
    frameCount = frameCount;
    associated.box.w = GetWidth();
    SetFrame(0);
}

void Sprite::SetFrameTime(float frameTime) {
    frameTime = frameTime;
}

Vec2 Sprite::GetScale() {
    return scale;
}
