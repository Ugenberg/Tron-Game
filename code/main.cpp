#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "main.h"
#include "menu.h"
#include "game.h"

using namespace sf;

int main() {
    // Window declaration
	RenderWindow window(VideoMode(W, H), "Tron", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);  // So game is stabilized
	window.setKeyRepeatEnabled(false);    // So player don't crash somehow

    // Functions declaration
    Menu menu;
    Game game;

    // Menu loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) {
					menu.MoveUp();
				}
				if (event.key.code == Keyboard::Down) {
					menu.MoveDown();
				}
				if (event.key.code == Keyboard::Enter) {
					menu.Enter(window);
				}
			}
		}

        // First start menu, then if Enter is pressed, start game
		if (game.islaunched() == false) {
			menu.startScreen(window);
		}
		if (game.islaunched() == true) {
			game.startGame(window);
		}
	}
	return 0;
}
