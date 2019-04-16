#ifndef TILEMAP_H
#define TILEMAP_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Component.hpp"
#include "GameObject.hpp"
#include "GameData.hpp"
#include "TileSet.hpp"
#include "Vec2.hpp"
#include <string>
#include <vector>

class TileMap : public Component {
    public:
        TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);

        void Load(const std::string& file);

        void SetTileSet(TileSet* tileSet);

        int& At(int x, int y, int z = 0);

        void Render();
        
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

        bool Is(GameData::Types type) const override;

        void Update(float dt) override;

        int GetWidth();

        int GetHeight();

        int GetDepth();
    
        void SetParallax(int layer, float xFactor, float yFactor);

        const GameData::Types Type = GameData::Types::TileMap;
    private:
        std::vector<int> tileMatrix;
        std::vector<Vec2> layerParallax;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
};

#endif
