#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Menu{
    public:
        void MoveUp();
        void MoveDown();
        void Enter(RenderWindow &window);
        void startScreen(RenderWindow &window);
};
