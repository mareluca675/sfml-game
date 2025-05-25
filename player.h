#include <SFML/Graphics.hpp>
#include "item.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
	float score;
	float mousePower;
	float criticalChance;
public:
	Player();
	void buyItem(Item&);

	// Setters
	void setScore(float newScore) { score = newScore; }
	void setMousePower(float power) { mousePower = power; }
	void setCriticalChance(float chance) { criticalChance = chance; }	

	// Getter and Setter for score
	float getScore() const { return score; }
	float getMousePower() const { return mousePower; }
	float getCriticalChance() const { return criticalChance; }
};

#endif

