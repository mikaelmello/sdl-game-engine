#ifndef SPRITE_H
#define SPRITE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL

#include <string>
#include "SDL_include.h"
#include "Component.hpp"

class Sprite : public Component {
    public:
        Sprite(GameObject& associated);

        Sprite(GameObject& associated, const std::string& file);

        ~Sprite();

        void Open(const std::string& file);

        void SetClip(int x, int y, int w, int h);

        void Update();

        bool Is(const std::string& type);

        void Render();

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
