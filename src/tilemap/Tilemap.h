#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "Preloader.h"
#include "SDL_include.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include "constants.h"
#include "CollisionKit.h"
#include "Camera.h"

class Tilemap{
public:
    Uint16 id;
    int width;
    int height;
    int x;
    int y;
    double scale; 
    int tilesize;
    bool visible;
    Texture* tilesheet;
    std::string csv_data;
    std::vector<int> tileData;
    Tilemap(Uint16 id, Texture* tilesheet, int width, int height, int tilesize, int x, int y, double scale, bool visible);
    ~Tilemap();

    void drawTileMap(int sheetsize);
    void setTileRectIn(SDL_Rect &rect, int id, int sheetsize);
    void setX(int x_);
    void setY(int y_);
    void setScale(int scale_);
    void changeMapID(int ID);
    void updateTileData();
    int getX();
    int getY();
    int getScale();
    SDL_Rect getTilemapRect();
};
