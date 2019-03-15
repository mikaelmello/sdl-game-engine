

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Sprite.hpp"
#include "Game.hpp"
#include <stdexcept>
#include <string>

Sprite::Sprite() : texture(nullptr) {}

Sprite::Sprite(std::string file) : texture(nullptr) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (texture == nullptr) {
        throw std::runtime_error("Could not load texture from file " + file + ": " + IMG_GetError());
    }

    int return_code = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    if (return_code != 0) {
        throw std::runtime_error("Could not query invalid texture from " + file + ": " + IMG_GetError());
    }
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = { x, y, w, h };
}

void Sprite::Render(int x, int y) {
    SDL_Rect temp_rect = { x, y, clipRect.w, clipRect.h };
    int return_code = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &temp_rect);
    if (return_code != 0) {
        throw std::runtime_error("Could not copy sprite to rendering target: " + std::string(IMG_GetError()));
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

