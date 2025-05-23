#include "player.h"

Player::Player() {
	mousePower = 1.0f;
	criticalChance = 0.0f;
	equipment = List<Item>();
}

void Player::equipItem(Item item) {
	equipment.push_back(item);
	mousePower += item.getMousePower();
	criticalChance += item.getCriticalChance();
}