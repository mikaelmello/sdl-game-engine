

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Sprite.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Resources.hpp"
#include "Component.hpp"
#include <stdexcept>
#include <string>

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr), scale(1, 1) {}

Sprite::Sprite(GameObject& associated, const std::string& file) : Sprite(associated) {
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
    SDL_Rect temp_rect = { x, y, clipRect.w, clipRect.h };
    int return_code = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &temp_rect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (return_code != 0) {
        throw std::runtime_error("Could not copy sprite to rendering target: " + std::string(IMG_GetError()));
    }
}

void Sprite::Render() {
    Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Update(float dt) {}

bool Sprite::Is(const std::string& type) const {
    return type == std::string("Sprite");
}

int Sprite::GetWidth() const {
    return round(scale.x * width);
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

Vec2 Sprite::GetScale() {
    return scale;
}
