#include "UI.h"

UI_Component::UI_Component(int x, int y, Texture* texture) : x(x), y(y), texture(texture){
    rect.x = x;
    rect.y = y;
    rect.w = texture->getWidth() * texture->getScale();
    rect.h = texture->getHeight() * texture->getScale();
    rect_in_tex.x = 0;
    rect_in_tex.y = 0;
    rect_in_tex.w = texture->getWidth();
    rect_in_tex.h = texture->getHeight();
}

UI_Component::~UI_Component(){
}

void UI_Component::draw_template(){
    Renderer::drawTexture(texture, rect_in_tex, rect);
}