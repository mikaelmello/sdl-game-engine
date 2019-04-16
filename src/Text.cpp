
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Text.hpp"
#include "Game.hpp"
#include "GameData.hpp"
#include "Resources.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include <string>
#include <memory>


Text::Text(GameObject& associated, const std::string& fontFile, int fontSize, TextStyle style,
    const std::string& text, SDL_Color color) : Component(associated), fontFile(fontFile),
    fontSize(fontSize), style(style), text(text), color(color), blink(false), display(true) {
    RemakeTexture();
}

Text::~Text() {}

void Text::Update(float dt) {
    if (blink) {
        blinkTimer.Update(dt);
        if (blinkTimer.Get() > blinkPeriod) {
            blinkTimer.Restart();
            display = !display;
        }
    }
}

void Text::Render() {
    if (!display) {
        return;
    }

    Vec2 cameraPos = Camera::pos;
    SDL_Rect clipRect = { 0, 0, (int)associated.box.w, (int)associated.box. h };
    SDL_Rect tempRect = { (int)(associated.box.x - cameraPos.x), (int)(associated.box.y - cameraPos.y), clipRect.w, clipRect.h };
    int return_code = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &tempRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (return_code != 0) {
        throw std::runtime_error("Could not copy sprite to rendering target: " + std::string(IMG_GetError()));
    }
}

bool Text::Is(GameData::Types type) const {
    return type == GameData::Types::Text;
}

void Text::SetText(const std::string& text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(const std::string& fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::SetBlink(bool blink, float period) {
    this->blink = blink;
    if (blink) {
        blinkPeriod = period;
    }
}

void Text::RemakeTexture() {
    font = Resources::GetFont(fontFile, fontSize);
    
    SDL_Surface* surface = nullptr;

    switch(style) {
        case TextStyle::BLENDED:
            surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
            break;
        case TextStyle::SOLID:
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;
        case TextStyle::SHADED:
            surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, { 0, 0, 0, 1 });
            break;
    }

    if (surface == nullptr) {
        throw std::runtime_error("Could not create surface from text component");
    }

    associated.box.w = surface->w;
    associated.box.h = surface->h;
    SDL_Texture* textureFromSurface = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    texture = std::shared_ptr<SDL_Texture>(textureFromSurface, [=](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    SDL_FreeSurface(surface);
}
