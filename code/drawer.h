#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Drawer {
    public:
        Font font;
        Text text[25];
        Sprite sprite[25];
        ConvexShape triangle[25];
        ConvexShape rectangle[25];

        float alpha = 255;

        virtual void draw(RenderWindow &window);
};

