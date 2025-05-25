#include "player.h"

Player::Player() {
	score = 0.0f;
	mousePower = 1.0f;
	criticalChance = 0.0f;
}

void Player::buyItem(Item item) {
	score -= item.getCost();
	mousePower *= item.getMousePower();
	criticalChance += item.getCriticalChance();
	item.setCost(item.getCost() * 1.33f);
	item.setMousePower(item.getMousePower() * 1.33f);
	item.setCriticalChance(item.getCriticalChance() * 1.15f);
}