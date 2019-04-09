#ifndef TEXT_H
#define TEXT_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "GameObject.hpp"
#include "Timer.hpp"
#include "Component.hpp"
#include <string>
#include <memory>

class Text : public Component {
    public:
        enum TextStyle { SOLID, SHADED, BLENDED };

        Text(GameObject& associated, const std::string& fontFile, int fontSize, TextStyle style, const std::string& text, SDL_Color color);

        ~Text();

        void Update(float dt) override;

        void Render() override;

        bool Is(const std::string& type) const override;

        void SetText(const std::string& text);

        void SetColor(SDL_Color color);

        void SetStyle(TextStyle style);

        void SetFontFile(const std::string& fontFile);

        void SetFontSize(int fontSize);

        void SetBlink(bool blink, float blinkPeriod);
    private:
        void RemakeTexture();

        std::shared_ptr<TTF_Font> font;
        std::shared_ptr<SDL_Texture> texture;

        std::string text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color;
        bool blink;
        bool display;
        float blinkPeriod;
        Timer blinkTimer;

};

#endif
