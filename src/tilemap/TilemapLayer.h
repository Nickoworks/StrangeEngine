#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "SDL_include.h"
#include <vector>
#include <iostream>

class TilemapLayer{
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
    TilemapLayer(Uint16 id, Texture* tilesheet, int width, int height, int tilesize, int x, int y, double scale, bool visible);
    ~TilemapLayer();

    void drawLayer();
    void setTileRectIn(SDL_Rect &rect, int id, int sheetsize);
    void changeMapID(int ID);
    void updateTileData();
};
