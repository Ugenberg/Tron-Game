#include "settings.h"

using namespace sf;

// Creating global variable, so we can use and modify it in other files
extern float pSpeed = 3.5;

// Function to change speed
void Settings::changeSpeed(float a) {
    if (a == 3.5) {
        printf ("Value reseted\n");
        pSpeed = 3.5;
    }
    else if (a != 3.5) {
        printf ("Value updated\n");
        pSpeed = pSpeed + a;
    }
}

// Function to get player speed
int Settings::getSpeed() {
    printf ("Value sent\n");
    return pSpeed;
}
