#ifndef SPRITE_H
#define SPRITE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL

#include <string>
#include "SDL_include.h"

class Sprite {
    public:
        Sprite();

        Sprite(const std::string& file);

        ~Sprite();

        void Open(const std::string& file);

        void SetClip(int x, int y, int w, int h);

        void Render(int x, int y);

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
