#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "main.h"
#include "game.h"
#include "menu.h"
#include "player.h"

using namespace sf;

// Bool variables
bool pause = false;
bool crashed = false;
bool launchedGame = false;

// Set game launch bool to true
void Game::launchgame() {
	launchedGame = true;
}

// Check whether game is launched
bool Game::islaunched() {
	if (launchedGame == true) {
		return true;
	}
	else {
		return false;
	}
}

// Game function
void Game::startGame(RenderWindow &window) {
	// Background declaration
    Texture texture;
	texture.loadFromFile("background.png");
	Sprite sBackground(texture);

    // Font Declaration
	Font font;
	if (!font.loadFromFile("arial.ttf")) {
		printf("Error: Loading a font\n");
	}

    // Random initial positions and directions declarations
	srand(time(NULL));
	int x1 = (W / 4) + rand() % (W - (W / 2));
	int y1 = (H / 4) + rand() % (H - (H / 2));
	int x2 = (W / 4) + rand() % (W - (W / 2));
	int y2 = (H / 4) + rand() % (H - (H / 2));
	int dir1 = rand() % 4;
	int dir2 = rand() % 4;
	Player p1(x1, y1, dir1, Color::Cyan);
	Player p2(x2, y2, dir2, Color::Magenta);
	p1.changeDirection(dir1);
    p2.changeDirection(dir2);

	// Players and Edges wall declaration
	VertexArray Wall;
	VertexArray p1Wall(LinesStrip);
	VertexArray p2Wall(LinesStrip);

	// Score declaration for each player
	int score1 = 0;
	int score2 = 0;
	Text text1, text2;
	text1.setFont(font);
	text2.setFont(font);
	text1.setString(std::to_string(score1));
	text2.setString(std::to_string(score2));
	text1.setCharacterSize(50);
	text2.setCharacterSize(50);
	text1.setFillColor(p1.getColor());
	text2.setFillColor(p2.getColor());
	FloatRect textBox1 = text1.getLocalBounds();
	FloatRect textBox2 = text2.getLocalBounds();
	text1.setOrigin(textBox1.left + textBox1.width / 2, textBox1.top + textBox1.height / 2);
	text2.setOrigin(textBox2.left + textBox2.width / 2, textBox2.top + textBox2.height / 2);
	text1.setPosition(Vector2f(W / 10.5, H / 20));
	text2.setPosition(Vector2f(W / 1.11, H / 20));

    // Width edges wall declaration
	for (int j = 0; j <= 5; j++) {
		for (int i = 0; i < W; i++) {
			Wall.append(Vertex(Vector2f(i, j), Color(123, 17, 237)));
			Wall.append(Vertex(Vector2f(i, H - 1 - j), Color(123, 17, 237)));
            // Recognizing edge wall by players
			p1.setSingleWall(i, j);
			p1.setSingleWall(i, H - 1 - j);
			p2.setSingleWall(i, j);
			p2.setSingleWall(i, H - 1 - j);
		}
	}
    // Heigth edges wall declaration
	for (int j = 0; j <= 5; j++) {
		for (int i = 0; i < H; i++) {
			Wall.append(Vertex(Vector2f(j, i), Color(123,17,237)));
			Wall.append(Vertex(Vector2f(W - 1 - j, i), Color(123, 17, 237)));
            // Recognizing edge wall by players
			p1.setSingleWall(j, i);
			p1.setSingleWall(W - 1 - j, i);
			p2.setSingleWall(j, i);
			p2.setSingleWall(W - 1 - j, i);
		}
	}
	Menu menu;
	// Game loop
	while (launchedGame) {
		Event event;
		// Event loop
		while (window.pollEvent(event)) {
			// Game final exit (to prevent error from escape)
			if (event.type == Event::Closed)
				window.close();
            // Game exit to menu
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                launchedGame = false;
                menu.startScreen(window);
			}
            // Game pause
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
                pause = !pause;
            }
		}
		// Stops moving when game is paused
        if (!pause) {
            // Keyboard input
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                p1.changeDirection(up);
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                p1.changeDirection(down);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                p1.changeDirection(left);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                p1.changeDirection(right);
            }
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                p2.changeDirection(up);
            }
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                p2.changeDirection(down);
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                p2.changeDirection(left);
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                p2.changeDirection(right);
            }

            // Initializing vertex for each player movement
            Vertex A = p1.move();
            Vertex B = p2.move();

            // Check whether one of players crashed into something then gives score
            if (p1.isCrashed(A.position.x, A.position.y, p1.getPosition().x, p1.getPosition().y)) {
                score2++;
            }
            if (p2.isCrashed(B.position.x, B.position.y, p2.getPosition().x, p2.getPosition().y)) {
                score1++;
            }

            // Check whether one of players crashed into something then informs about collision
            if (p1.isCrashed(A.position.x, A.position.y, p1.getPosition().x, p1.getPosition().y) ||
                p2.isCrashed(B.position.x, B.position.y, p2.getPosition().x, p2.getPosition().y)) {
                crashed = !crashed;
            }

            // Updating players position and increases player wall left behind
            p1Wall.append(A);
            p1.setWall(A.position.x, A.position.y, p1.getPosition().x, p1.getPosition().y);
            p1.setWall(B.position.x, B.position.y, p2.getPosition().x, p2.getPosition().y);
            p1.update();
            p2Wall.append(B);
            p2.setWall(A.position.x, A.position.y, p1.getPosition().x, p1.getPosition().y);
            p2.setWall(B.position.x, B.position.y, p2.getPosition().x, p2.getPosition().y);
            p2.update();

            // Restart if crashed
            if (crashed) {
                // Stop time for second beetwen each crash
                sleep(milliseconds(1000));
                // Clear walls
                Wall.clear();
                p1Wall.clear();
                p2Wall.clear();
                // Reset players walls
                p1.wallReset();
                p2.wallReset();
                // Get new starting positions and directions for each player
                x1 = (W / 4) + rand() % (W - (W / 2));
                y1 = (H / 4) + rand() % (H - (H / 2));
                x2 = (W / 4) + rand() % (W - (W / 2));
                y2 = (H / 4) + rand() % (H - (H / 2));
                dir1 = rand() % 4;
                dir2 = rand() % 4;
                p1.setPosition(x1, y1);
                p2.setPosition(x2, y2);
                p1.changeDirection(dir1);
                p2.changeDirection(dir2);
                // Recreate width edge walls
                for (int j = 0; j <= 5; j++) {
                    for (int i = 0; i < W; i++) {
                        Wall.append(Vertex(Vector2f(i, j), Color(123, 17, 237)));
                        Wall.append(Vertex(Vector2f(i, H - 1 - j), Color(123, 17, 237)));
                    }
                }
                // Recreate heigth edge walls
                for (int j = 0; j <= 5; j++) {
                    for (int i = 0; i < H; i++) {
                        Wall.append(Vertex(Vector2f(j, i), Color(123, 17, 237)));
                        Wall.append(Vertex(Vector2f(W - 1 - j, i), Color(123, 17, 237)));
                    }
                }
                crashed = false;
            }
		}
		// Draw background
        window.draw(sBackground);
        // Draw players on top of background
		window.draw(p1.getShape());
		window.draw(p2.getShape());
        // Draw walls on top of players and background
		window.draw(Wall);
		window.draw(p1Wall);
		window.draw(p2Wall);
		// Set scores to string and draw them on top of the rest
        text1.setString(std::to_string(score1));
		text2.setString(std::to_string(score2));
		window.draw(text1);
		window.draw(text2);
        // Display everything
		window.display();
	}
}
