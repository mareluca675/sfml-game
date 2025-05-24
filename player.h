#include <SFML/Graphics.hpp>
#include "item.h"
#include "list.hpp"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
	float mousePower;
	float criticalChance;
	List<Item> equipment;
	
public:
	Player();
	void equipItem(Item);
	Item getItem(int index) { return equipment.at(index); }
	float getMousePower() { return mousePower; }
	float getCriticalChance() { return criticalChance; }
	// setters
	void setMousePower(float power) { mousePower = power; }
	void setCriticalChance(float chance) { criticalChance = chance; }	
};

#endif

