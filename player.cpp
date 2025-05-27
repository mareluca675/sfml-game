#include "player.h"

Player::Player() {
	score = 0.0f;
	mousePower = 1.0f;
	criticalChance = 99.0f;
}

void Player::buyItem(Item &item) {
	// Update player's score, mouse power, and critical chance
	score -= item.getCost();
	score = std::round(score * 100.0f) / 100.0f;
	mousePower = std::round((mousePower + item.getMousePower()) * 100.0f) / 100.0f;
	criticalChance = criticalChance + item.getCriticalChance();
	if (criticalChance > 100.0f) {
		criticalChance = 100.0f; // Cap critical chance at 100%
	}
	
	// Update item's cost, mouse power, and critical chance
	item.setCost(item.getCost() * 1.25f);
	item.setCost(std::round(item.getCost() * 100.0f) / 100.0f);
	item.setMousePower(item.getMousePower() * 1.25f);
	item.setCost(std::round(item.getCost() * 100.0f) / 100.0f);
}