#ifndef SPRITE_H
#define SPRITE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL

#include <string>
#include "SDL_include.h"
#include "Component.hpp"
#include "GameObject.hpp"

class Sprite : public Component {
    public:
        Sprite(GameObject& associated);

        Sprite(GameObject& associated, const std::string& file);

        ~Sprite();

        void Open(const std::string& file);

        void SetClip(int x, int y, int w, int h);

        void Update(float dt) override;

        bool Is(const std::string& type) override;

        void Render() override;

        int GetWidth() const;

        int GetHeight() const;

        bool IsOpen() const;
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};

#endif
