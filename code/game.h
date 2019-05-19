#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Game {
    public:
        void launchgame();
        bool islaunched();
        void startGame(RenderWindow &window);
};
