#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "drawer.h"

using namespace sf;

// Menu draw function
void Drawer::draw(RenderWindow &window) {
    // Clears window each time
	window.clear(Color::Black);

	// Load font
	if (!font.loadFromFile("BebasNeue-Regular.otf")) {
		printf("Error: Loading a font\n");
	}

    // Draw menu text
	for (int i = 0; i < 25; i++) {
		window.draw(text[i]);
	}

    // Draw text menu selection
	for (int i = 0; i < 25; i++) {
		window.draw(sprite[i]);
		window.draw(triangle[i]);
	}
	window.display();
}
