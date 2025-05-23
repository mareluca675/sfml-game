#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "game.h"

int main() {
	Game world = Game();

    // Main loop
    while (true) {
        if(!world.performSetupMain()) {
			std::cout << "ERROR: Couldn't perfrom setup.";
			return 1;
		}

		if (!world.runGame()) {
			return 0;
		}
    }

    return 0;
}
