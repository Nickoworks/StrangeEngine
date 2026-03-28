#include "BlockTilemap.h"

BlockTilemap::BlockTilemap(Uint16 id, int tilesize, double scale, bool visible, int width, int height, int x, int y) : id(id),
tilesize(tilesize), scale(scale), visible(visible), width(width), height(height), x(x), y(y){
    std::string path_ = "../res/map.dat/" + std::to_string(id) + "_.csv";

    // add poll error if file is empty!!

    // width = Tilemap::rect_tilemap.w / tilesize;
    // height = Tilemap::rect_tilemap.h / tilesize;
    csv_data = load_file(path_);

    std::istringstream iss(csv_data);
    std::string line;
    SDL_Rect rect;
    int currTile = 0;

    for(int y = 0; y < height; y++){
        if(!std::getline(iss, line)){
            break;
        }
        std::istringstream iss_(line);
        for(int x = 0; x < width; x++){
            std::string token;
            if(!std::getline(iss_, token, ',')){
                break;
            }
            tileData.push_back(std::stoi(token));
            if(std::stoi(token) == -1){
                continue;
            }
        }
    }

    int scaled_tile = tilesize * scale;

    for(int y = 0; y < height; y++){
        rect.y = BlockTilemap::y + (y * scaled_tile);
        for(int x = 0; x < width; x++){
            rect.x = BlockTilemap::x + (x * scaled_tile);
            if(tileData[x+y*width] == 19 || tileData[x+y*width] == 255){
                Physics::createStaticBody(Vector2D<float>((int)rect.x, (int)rect.y), Vector2D<float>((int)(tilesize*scale), (int)(tilesize*scale)), 0, "block_tile" + std::to_string(currTile));
                currTile++;
            }
        }
    }
}

BlockTilemap::~BlockTilemap(){}

void BlockTilemap::update(){
    tileRectData.clear();
    SDL_Rect rect;
    int currTile = 0;
    rect.w = tilesize * scale;
    rect.h = tilesize * scale;

    for(int y = 0; y < height; y++){
        rect.y = (y * (tilesize * scale)) - Camera::y;
        for(int x = 0; x < width; x++){
            rect.x = (x * (tilesize * scale)) - Camera::x;
            if(tileData[x+y*width] == -1){
                continue;
            }
            tileRectData.push_back(rect);
            if(visible){
                Renderer::drawRect({static_cast<int>(Physics::getStaticBody(0, "block_tile" + std::to_string(currTile))->position.x - Camera::x),
                                    static_cast<int>(Physics::getStaticBody(0, "block_tile" + std::to_string(currTile))->position.y - Camera::y),
                                    static_cast<int>(Physics::getStaticBody(0, "block_tile" + std::to_string(currTile))->size.x),
                                    static_cast<int>(Physics::getStaticBody(0, "block_tile" + std::to_string(currTile))->size.y)
                                    }, {255, 0, 0, 0});
            }
            currTile++;
        }
    }
}

void BlockTilemap::changeMapID(Uint16 id_){
    BlockTilemap::id = id_;
    std::string path_ = "../res/map.data/" + std::to_string(id) + ".csv";
    csv_data = load_file(path_); 
}
