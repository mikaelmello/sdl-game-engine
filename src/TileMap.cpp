#include "TileMap.hpp"
#include "TileSet.hpp"
#include "Helpers.hpp"
#include "Camera.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>
#include <fstream>
#include <sstream>

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet) : Component(associated), tileSet(tileSet) {
    Load(file);
}

void TileMap::Load(const std::string& file) {
    std::ifstream infile(file);
    std::string line;
    int index = 0;
    
    while (index < 3 && std::getline(infile, line, ',')) {
        int number = std::stoi(line);
        switch (index) {
            case 0: mapWidth  = number; break;
            case 1: mapHeight = number; break;
            case 2: mapDepth  = number; break;
        }

        index++;
    }

    long long times = mapWidth * mapHeight * mapDepth;

    for (long long i = 0; i < times; i++) {
        std::getline(infile, line, ',');
        if (Helpers::is_whitespace(line)) {
            i--;
            continue;
        }
        int number = std::stoi(line);
        tileMatrix.push_back(number - 1);
    }

    // default parallax factor
    for (int i = 0; i < mapDepth; i++) {
        layerParallax.push_back({0, 0});
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

void TileMap::SetParallax(int layer, float xFactor, float yFactor) {
    if (layer < 0 || layer >= mapDepth) {
        throw std::invalid_argument("Invalid layer to add parallax factors");
    }

    layerParallax[layer] = { xFactor, yFactor };
}

int& TileMap::At(int x, int y, int z) {
    int index = 0;
    index += mapWidth * mapHeight * z;
    index += mapWidth * y;
    index += x;

    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            int x = i * tileSet->GetTileWidth() - cameraX - cameraX * layerParallax[layer].x;
            int y = j * tileSet->GetTileHeight() - cameraY - cameraY * layerParallax[layer].y;
            tileSet->RenderTile((unsigned)At(i, j, layer), x, y);
        }
    }
}

void TileMap::Render() {
    for (int i = 0; i < mapDepth; i++) {
        RenderLayer(i, Camera::pos.x, Camera::pos.y);
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

bool TileMap::Is(const std::string& type) const {
    return type == std::string("TileMap");
}


int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(float dt) {}
