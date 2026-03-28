#pragma once
#include "SDL_include.h"
#include <iostream>
#include <sstream>
#include "Texture.h"
#include "load_file.h"
#include "Camera.h"
#include "Physics.h"
#include "Vector2D.h"

class BlockTilemap{
public:
    Uint16 id;
    int x;
    int y;
    int width;
    int height;
    int scale; 
    int tilesize;
    bool visible;
    std::string csv_data;
    std::vector<int> tileData;
    std::vector<SDL_Rect> tileRectData;

    BlockTilemap(Uint16 id, int tilesize, double scale, bool visible, int width, int height, int x, int y);
    BlockTilemap();
    ~BlockTilemap();
    void update();
    void changeMapID(Uint16 id_);
};
