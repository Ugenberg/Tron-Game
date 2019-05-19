#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "main.h"
#include "menu.h"
#include "game.h"
#include "drawer.h"
#include "settings.h"

using namespace sf;

// Functions declaration
Drawer drawer;
Game game;

// Selection start at 4, because we made rectangles from top
int selectedLink = 4;

bool inSettings = false;

// Function to control menu moving up
void Menu::MoveUp() {
	if (selectedLink > 4) {
		selectedLink = selectedLink - 1;
	}
};

// Function to control menu moving down
void Menu::MoveDown() {
	if (selectedLink < 6 && inSettings == false) {
		selectedLink = selectedLink + 1;
	}
	else if (selectedLink < 7 && inSettings == true) {
        selectedLink = selectedLink + 1;
	}
};

// Function to control what option was selected
void Menu::Enter(RenderWindow &window) {
    if (!inSettings) {
        if (selectedLink == 4) {
            drawer.alpha = 0;
            printf ("Play\n");
            game.launchgame();
        }
        if (selectedLink == 5) {
            printf ("Settings\n");
            inSettings = true;
            selectedLink = 4;
            startScreen(window);
        }
        if (selectedLink == 6) {
            printf ("Exit\n");
            window.close();
        }
    }
    if (inSettings) {
        Settings settings;
        if (selectedLink == 4) {
            printf ("Speed up\n");
            settings.changeSpeed(0.25);
        }
        if (selectedLink == 5) {
            printf ("Speed down\n");
            settings.changeSpeed(-0.25);
        }
        if (selectedLink == 6) {
            printf ("Speed reset\n");
            settings.changeSpeed(3.5);
        }
        if (selectedLink == 7) {
            printf ("Back to main menu\n");
            inSettings = false;
            selectedLink = 4;
            startScreen(window);
        }
    }
}

// Main menu function
void Menu::startScreen(RenderWindow &window) {
    if (!inSettings) {
        // Drawing menu (and game) title
        drawer.alpha = drawer.alpha - 5;
        drawer.text[0].setFont(drawer.font);
        drawer.text[0].setString("Tron");
        drawer.text[0].setCharacterSize(120);
        drawer.text[0].setFillColor(Color(0, 255, 255, drawer.alpha));
        drawer.text[0].setPosition(W / 3, H / 10);
        if (drawer.alpha == 0) {
            drawer.alpha = 255;
        }
        // Drawing start option
        drawer.text[1].setFont(drawer.font);
        drawer.text[1].setString("Start");
        drawer.text[1].setCharacterSize(60);
        drawer.text[1].setFillColor(Color(123, 17, 237));
        drawer.text[1].setPosition(W / 3, H / 10*4);
        // Drawing settings option
        drawer.text[2].setFont(drawer.font);
        drawer.text[2].setString("Settings");
        drawer.text[2].setCharacterSize(60);
        drawer.text[2].setFillColor(Color(123, 17, 237));
        drawer.text[2].setPosition(W / 3, H / 10*5);
        // Drawing quit option
        drawer.text[3].setFont(drawer.font);
        drawer.text[3].setString("Quit");
        drawer.text[3].setCharacterSize(60);
        drawer.text[3].setFillColor(Color(123, 17, 237));
        drawer.text[3].setPosition(W / 3, H / 10*6);
        // Drawing option selection triangle
        drawer.triangle[0].setPointCount(3);
        drawer.triangle[0].setPoint(0, Vector2f(0.f, 0.f));
        drawer.triangle[0].setPoint(1, Vector2f(20.f, 0.f));
        drawer.triangle[0].setPoint(2, Vector2f(0.f, 20.f));
        drawer.triangle[0].setFillColor(Color(123, 17, 237));
        drawer.triangle[0].setPosition(W / 3, (H+10)/10 * selectedLink-3);
        // Drawing credits
        drawer.text[4].setFont(drawer.font);
        drawer.text[4].setString(L"Game by\nJarosław Chudaś");
        drawer.text[4].setCharacterSize(25);
        drawer.text[4].setFillColor(Color(255, 0, 255));
        drawer.text[4].setPosition(W / 1.25, H / 1.12);
        // Draw everything
        drawer.draw(window);
    }
    if (inSettings) {
        // Drawing menu (and game) title
        drawer.alpha = drawer.alpha - 5;
        drawer.text[0].setFont(drawer.font);
        drawer.text[0].setString("Tron");
        drawer.text[0].setCharacterSize(120);
        drawer.text[0].setFillColor(Color(0, 255, 255, drawer.alpha));
        drawer.text[0].setPosition(W / 3, H / 10);
        if (drawer.alpha == 0) {
            drawer.alpha = 255;
        }
        // Drawing change speed option
        drawer.text[1].setFont(drawer.font);
        drawer.text[1].setString("Player speed +0.25");
        drawer.text[1].setCharacterSize(60);
        drawer.text[1].setFillColor(Color(123, 17, 237));
        drawer.text[1].setPosition(W / 3, H / 10*4);
         // Drawing change speed option
        drawer.text[2].setFont(drawer.font);
        drawer.text[2].setString("Player speed -0.25");
        drawer.text[2].setCharacterSize(60);
        drawer.text[2].setFillColor(Color(123, 17, 237));
        drawer.text[2].setPosition(W / 3, H / 10*5);
         // Drawing reset speed option
        drawer.text[3].setFont(drawer.font);
        drawer.text[3].setString("Players speed reset");
        drawer.text[3].setCharacterSize(60);
        drawer.text[3].setFillColor(Color(123, 17, 237));
        drawer.text[3].setPosition(W / 3, H / 10*6);
         // Drawing back menu option
        drawer.text[4].setFont(drawer.font);
        drawer.text[4].setString("Back");
        drawer.text[4].setCharacterSize(60);
        drawer.text[4].setFillColor(Color(123, 17, 237));
        drawer.text[4].setPosition(W / 3, H / 10*7);
        // Drawing option selection triangle
        drawer.triangle[0].setPointCount(3);
        drawer.triangle[0].setPoint(0, Vector2f(0.f, 0.f));
        drawer.triangle[0].setPoint(1, Vector2f(20.f, 0.f));
        drawer.triangle[0].setPoint(2, Vector2f(0.f, 20.f));
        drawer.triangle[0].setFillColor(Color(123, 17, 237));
        drawer.triangle[0].setPosition(W / 3, (H+10)/10 * selectedLink-3);
        // Draw everything
        drawer.draw(window);
    }
};
