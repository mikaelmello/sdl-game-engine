#ifndef TILESET_H
#define TILESET_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Sprite.hpp"
#include <string>

class TileSet {
    public:
        TileSet(int tileWidth, int tileHeight, const std::string& file);

        void RenderTile(unsigned int index, float x, float y);

        int GetTileWidth();

        int GetTileHeight();

    private:

        Sprite tileSet;

        int rows;
        int columns;

        int tileWidth;
        int tileHeight;
};

#endif
