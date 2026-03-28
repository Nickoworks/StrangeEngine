#include "Text.h"

Text::Text(std::string text, int x, int y, int size, TTF_Font* font, SDL_Color color) : 
text(text), 
x(x), 
y(y), 
size(size), 
font(font),
color(color){
}

Text::~Text(){
}

void Text::draw(){
    int currlinenum = 0;
    std::vector<std::string> lines;
    std::string currline;

    std::istringstream str(text);
    int textWidth, textHeight;

    while(std::getline(str, currline)){
        lines.push_back(currline);
    }

    for(int i = 0; i < lines.size(); i++){
        TTF_SizeText(font, lines[i].c_str(), &textWidth, &textHeight);
        SDL_Rect rect_text;
        rect_text.x = x;
        rect_text.y = y + (currlinenum * size * textHeight);
        rect_text.w = textWidth * size;
        rect_text.h = textHeight * size;

        // SDL_Surface* surfText = TTF_RenderText_Solid(font, lines[i].c_str(), color);
        SDL_Surface* surfText = TTF_RenderUTF8_Solid(font, lines[i].c_str(), color);
        SDL_Surface* formattedSurf = SDL_ConvertSurfaceFormat(surfText, SDL_PIXELFORMAT_RGBA32, 0);
        Renderer::drawSurface(formattedSurf, rect_text, "text");
        SDL_FreeSurface(surfText);
        SDL_FreeSurface(formattedSurf);
        currlinenum++;
    }
}

void Text::change_text(std::string text_){
    text = text_;
}

void Text::changeColor(SDL_Color color){
    Text::color = color;
}

void Text::close_ttf(){
    TTF_CloseFont(font);
}

int Text::get_size(){
    return size;
}