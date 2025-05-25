#include "player.h"

Player::Player() {
	score = 10000000.0f;
	mousePower = 1.0f;
	criticalChance = 0.0f;
}

void Player::buyItem(Item &item) {
	// Update player's score, mouse power, and critical chance
	score -= item.getCost();
	score = std::round(score * 100.0f) / 100.0f;
	mousePower = std::round((mousePower + item.getMousePower()) * 100.0f) / 100.0f;
	criticalChance = std::round((criticalChance + item.getCriticalChance()) * 100.0f) / 100.0f;
	
	// Update item's cost, mouse power, and critical chance
	item.setCost(item.getCost() * 1.25f);
	item.setMousePower(item.getMousePower() * 1.25f);
	item.setCriticalChance(item.getCriticalChance() * 1.25f);
}