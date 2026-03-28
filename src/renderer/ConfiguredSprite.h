#pragma once
struct ConfiguredSprite{
public:
    bool rect;
    bool rect_in;
    ConfiguredSprite(bool rect, bool rect_in);
    ~ConfiguredSprite();
};

// don't use now