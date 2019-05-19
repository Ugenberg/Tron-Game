#include "main.h"
#include "player.h"
#include "settings.h"

using namespace sf;

// Function to initialize player
Player::Player(float startX, float startY, int startDirection, Color Color) {
	// Starting position coordinates
	position.x = startX;
	position.y = startY;
    // Size and position
	pShape.setSize(Vector2f(6, 3));
	pShape.setPosition(position);
    // Direction
	direction = startDirection;
	changeDirection(startDirection);
    // Color
	pShape.setFillColor(Color);
	pColor = Color;
    // Set copy of window size to keep track of player wall
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			pWall[j][i] = 0;
		}
	}
}

// Function to get player position
Vector2f Player::getPosition() {
	return position;
}

// Function to set player position
void Player::setPosition(int x, int y) {
	position = Vector2f(x, y);
}

// Function to get player shape
RectangleShape Player::getShape() {
	return pShape;
}

// Function to change player direction
void Player::changeDirection(int a) {
	if (a % 2 != direction % 2) {
		switch (a) {
            case up:
                pShape.setRotation(270);
                break;
            case down:
                pShape.setRotation(90);
                break;
            case left:
                pShape.setRotation(180);
                break;
            case right:
                pShape.setRotation(0);
                break;
            default:
                break;
        }
		direction = a;
	}
}

// Function to get player direction
int Player::getDirection() {
	return direction;
}

// Function to get player color
Color Player::getColor() {
	return pColor;
}

// Function to set player wall
void Player::setWall(int x1, int y1, int x2, int y2) {
	if (x1 == x2) {
		for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
			if(i > 0 && i < H) {pWall[i][x1] = 1;}
		}
	}
	else if (y1 == y2) {
		for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
			if (i > 0 && i < W) {pWall[y1][i] = 1;}
		}
	}
	pWall[(int)position.y][(int)position.x] = 0;
}

// Function to create wall that allow to recognize edge walls by player
void Player::setSingleWall(int x, int y) {
	if(x > 0 && y > 0 && x < W && y < H) {pWall[y][x] = 1;}
}

// Function to check whether player crashed into something
bool Player::isCrashed(int x1, int y1, int x2, int y2) {
	if (x1 == x2) {
		for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
			if (i > 0 && i < H && pWall[i][x1]) {return 1;}
		}
	}
	else if (y1 == y2) {
		for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
			if (i > 0 && i < W && pWall[y1][i]) {return 1;}
		}
	}
	return 0;
}

// Function to reset every wall connected to player
void Player::wallReset() {
	for (int i = 0; i < H; i++) {
		pWall[i].reset();
	}

	for (int j = 0; j <= 5; j++) {
		for (int i = 0; i < W; i++) {
			pWall[j][i] = 1;
			pWall[H-1-j][i] = 1;
		}
	}

	for (int j = 0; j <= 5; j++) {
		for (int i = 0; i < H; i++) {
			pWall[i][j] = 1;
			pWall[i][W-1-j] = 1;
		}
	}
}

// Function that allow player to move
Vertex Player::move() {
    Settings settings;
	Vector2f pos = position;
	switch (direction) {
        case up:
            position.y -= settings.getSpeed();
            break;
        case down:
            position.y += settings.getSpeed();
            break;
        case right:
            position.x += settings.getSpeed();
            break;
        case left:
            position.x -= settings.getSpeed();
            break;
        default:
            break;
	}
	return Vertex(pos, pColor);
}

// Function to update player position
void Player::update() {
	pShape.setPosition(position);
}
