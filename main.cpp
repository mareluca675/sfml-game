#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "game.h"

int main() {
	Game game = Game();

    // Main loop
    while (true) {
		if (!game.runGame()) {
			return 0;
		}
    }

    return 0;
}
