#include <SFML/Graphics.hpp>
#include "list.hpp"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
	float mousePower;
	float criticalChance;
	List<Item> equipment;
	Player();
public:
	void equipItem(Item);
	Item getItem(int index) { return equipment[index]; }
	float getMousePower() { return mousePower; }
	float getCriticalChance() { return criticalChance; }
}

#endif

