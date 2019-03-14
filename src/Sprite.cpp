

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Sprite.hpp"
#include "Game.hpp"
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

    Game game = Game::GetInstance();
    texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());

    if (texture == nullptr) {
        throw "Failed to load texture";
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = { x, y, w, h };
}

void Sprite::Render(int x, int y) {
    SDL_Rect temp_rect = { x, y, clipRect.w, clipRect.h };
    Game game = Game::GetInstance();
    SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &temp_rect);
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

