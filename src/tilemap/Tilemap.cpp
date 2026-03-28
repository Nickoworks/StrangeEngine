#include "Tilemap.h"

Tilemap::Tilemap(Uint16 id, Texture* tilesheet, int width, int height, int tilesize, int x, int y, double scale, bool visible) : id(id), tilesheet(tilesheet), 
width(width), height(height), tilesize(tilesize), x(x), y(y), scale(scale), visible(visible){
    Tilemap::csv_data = load_file("../res/map.dat/" + std::to_string(id) + ".csv");

    // add poll error if file is empty!!

    std::istringstream iss(csv_data);
    std::string line;

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
        }
    }
}

Tilemap::~Tilemap(){
    
}

void Tilemap::updateTileData(){
    tileData.clear();
    std::istringstream iss(csv_data);
    std::string line;

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
        }
    }   
}

void Tilemap::setTileRectIn(SDL_Rect &rect, int id, int sheetsize){
    int row = id / (sheetsize/tilesize);
    int col = id % (sheetsize/tilesize);

    rect.x = col * tilesize;
    rect.y = row * tilesize;
}

void Tilemap::drawTileMap(int sheetsize){
    if(visible){
        SDL_Rect rect;
        SDL_Rect rect_in;

        rect.w = (tilesize) * scale;
        rect.h = (tilesize) * scale;
        rect_in.w = tilesize;
        rect_in.h = tilesize;

        int scaled_tilesize = tilesize * scale;

        for(int y = 0; y < Tilemap::height; y++){
            rect.y = (Tilemap::y + (y * scaled_tilesize)) - Camera::y; 
            for(int x = 0; x < Tilemap::width; x++){
                rect.x = (Tilemap::x + (x * scaled_tilesize)) - Camera::x;
                setTileRectIn(rect_in, tileData[x+y*width], sheetsize);
                Renderer::drawTexture(tilesheet, rect_in, rect);
            }
        }
    }
}

void Tilemap::setX(int x_){
    Tilemap::x = x_;
}

void Tilemap::setY(int y_){
    Tilemap::y = y_;
}

void Tilemap::setScale(int scale_){
    Tilemap::scale = scale_;
}

int Tilemap::getX(){
    return Tilemap::x;
}

int Tilemap::getY(){
    return Tilemap::y;
}

int Tilemap::getScale(){
    return Tilemap::scale;
}

SDL_Rect Tilemap::getTilemapRect(){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width * tilesize;
    rect.h = height * tilesize;
    return rect;
}

void Tilemap::changeMapID(int ID){
    std::string path_ = "../res/map.data/" + std::to_string(ID) + ".csv"; 
    std::string csv_data_ = Preloader::load_file(path_);
    if(csv_data_ == " "){
        std::cout << "ERROR: map file not found or file is empty";
        return;
    }
    Tilemap::id = ID;
    Tilemap::csv_data = csv_data_;
    updateTileData();    
}
