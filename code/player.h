#pragma once

#include <SFML\Graphics.hpp>
#include <bitset>

using namespace sf;

enum directions {
	up,
	right,
	down,
	left
};

class Player {
    private:
        Vector2f position;

        RectangleShape pShape;

        int direction;

        Color pColor;

        std::bitset <W> pWall[H];

    public:
        Player(float startX, float startY, int startDirection, Color Color);

        Vector2f getPosition();

        void setPosition(int x, int y);

        RectangleShape getShape();

        void changeDirection(int a);

        int getDirection();

        int speed();

        void changeSpeed(float a);

        int getSpeed();

        Color getColor();

        void setWall(int x1, int y1, int x2, int y2);

        void setSingleWall(int x, int y);

        bool isCrashed(int x1, int y1, int x2, int y2);

        void wallReset();

        Vertex move();

        void update();
};
